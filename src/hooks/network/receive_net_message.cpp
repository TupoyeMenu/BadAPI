#include "common.hpp"
#include "core/data/packet_types.hpp"
#include "gta/gta_util.hpp"
#include "gta/net_game_event.hpp"
#include "gta/packet.hpp"
#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"
#include "network/netConnection.hpp"
#include "services/anti_cheat_bypass/anti_cheat_bypass.hpp"
#include "services/players/player_service.hpp"

#include <network/Network.hpp>
#include <network/P2pSecurity.hpp>
#include <network/netObjectIds.hpp>
#include <network/netTime.hpp>


inline void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
{
	if ((hnd.m_platform = buf.Read<uint8_t>(sizeof(hnd.m_platform) * 8)) != rage::rlPlatforms::PC)
		return;

	buf.ReadRockstarId(&hnd.m_rockstar_id);
	hnd.m_padding = buf.Read<uint8_t>(sizeof(hnd.m_padding) * 8);
}

namespace big
{
	bool try_read_secondary_header(rage::datBitBuffer& buffer)
	{
		auto data = buffer.Read<std::uint32_t>(20);
		return data == 0x8C253 || data == 0x8924F;
	}

	bool get_msg_type(rage::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		if (g_is_enhanced)
		{
			if (buffer.Read<int>(14) != 0x3246)
			{
				msgType = rage::eNetMessage::MsgInvalid;
				return false;
			}

			auto extended = buffer.Read<bool>(1);
			msgType       = buffer.Read<rage::eNetMessage>(extended ? 16 : 8);
			return true;
		}
		else
		{
			uint32_t pos;
			uint32_t magic;
			uint32_t length;
			uint32_t extended{};
			if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			    buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
			{
				msgType = rage::eNetMessage::MsgInvalid;
				return false;
			}
			length = extended ? 16 : 8;
			if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			    length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
				return true;
			else
				return false;
		}
	}

	static void script_id_deserialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		id.m_hash      = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);
		else
			id.m_position_hash = 0;

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
		else
			id.m_instance_id = -1;
	}

	static void script_id_serialize(CGameScriptId& id, rage::datBitBuffer& buffer)
	{
		buffer.Write<uint32_t>(id.m_hash, 32);
		buffer.Write<uint32_t>(id.m_timestamp, 32);

		if (id.m_position_hash != 0)
		{
			buffer.Write<bool>(true, 1);
			buffer.Write<uint32_t>(id.m_position_hash, 32);
		}
		else
		{
			buffer.Write<bool>(false, 1);
		}

		if (id.m_instance_id != -1)
		{
			buffer.Write<bool>(true, 1);
			buffer.Write<int32_t>(id.m_instance_id, 8);
		}
		else
		{
			buffer.Write<bool>(false, 1);
		}
	}

	void log_net_message(rage::eNetMessage message_type, rage::datBitBuffer& data_buffer, rage::netEvent* event, rage::SecurityPeer* sec_peer)
	{
		if (g.packet_logs == 1 || //ALL
		    (g.packet_logs == 2 && message_type != rage::eNetMessage::MsgCloneSync && message_type != rage::eNetMessage::MsgPackedCloneSyncACKs && message_type != rage::eNetMessage::MsgPackedEvents && message_type != rage::eNetMessage::MsgPackedReliables && message_type != rage::eNetMessage::MsgPackedEventReliablesMsgs && message_type != rage::eNetMessage::MsgNetArrayMgrUpdate && message_type != rage::eNetMessage::MsgNetArrayMgrSplitUpdateAck && message_type != rage::eNetMessage::MsgNetArrayMgrUpdateAck && message_type != rage::eNetMessage::MsgScriptHandshakeAck && message_type != rage::eNetMessage::MsgScriptHandshake && message_type != rage::eNetMessage::MsgScriptJoin && message_type != rage::eNetMessage::MsgScriptJoinAck && message_type != rage::eNetMessage::MsgScriptJoinHostAck && message_type != rage::eNetMessage::MsgRequestObjectIds && message_type != rage::eNetMessage::MsgInformObjectIds && message_type != rage::eNetMessage::MsgNetTimeSync)) //FILTERED
		{
			const char* packet_type = "<UNKNOWN>";
			for (const auto& p : packet_types)
			{
				if (p.second == (int)message_type)
				{
					packet_type = p.first;
					break;
				}
			}

			auto now        = std::chrono::system_clock::now();
			auto ms         = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
			auto timer      = std::chrono::system_clock::to_time_t(now);
			auto local_time = *std::localtime(&timer);

			std::string name = "";
			rage::rlGamerHandle rid{};

			if (sec_peer)
			{
				if (sec_peer->m_info.handle.m_platform == 3)
					rid = sec_peer->m_info.handle;
				else if (sec_peer->m_unverified_handle.m_platform == 3)
					rid = sec_peer->m_unverified_handle;
				name = sec_peer->m_info.name;
			}

			if (name.empty())
				name = "???";

			std::string log_msg = std::format("PKT | {} (0x{:X}) [size=0x{:X}, cxnId={:X}, peerId={}, msgId={}] from {} ({})",
			    packet_type,
			    (int)message_type,
			    data_buffer.GetDataLength(),
			    event->m_connection_identifier,
			    event->m_peer_id,
			    event->m_msg_id,
			    name,
			    rid.m_rockstar_id);

			static std::ofstream log(g_file_manager.get_project_file("./packets.log").get_path(), std::ios::app);
			log << "[" << std::put_time(&local_time, "%m/%d/%Y %I:%M:%S") << ":" << std::setfill('0') << std::setw(3) << ms.count() << " " << std::put_time(&local_time, "%p") << "] " << log_msg << std::endl;
			log.flush();
		}
	}

	bool is_host_of_session(rage::snSession* session, std::uint32_t peer_id)
	{
		if (!session || peer_id == -1)
			return false;

		if (auto player = session->get_player_by_token(session->m_host_token))
			return player->m_player_data.m_peer_id_2 == peer_id;

		return false;
	}

	bool hooks::receive_net_message(void* a1, rage::netConnectionManager* net_cxn_mgr, rage::netEvent* event)
	{
		void* message_data;
		int message_size;
		rage::netConnection::InFrame* frame  = nullptr;
		rage::netEventConnectionError* error = nullptr;

		if (event->get_event_type() == rage::netEvent::Type::ConnectionRequested || event->get_event_type() == rage::netEvent::Type::FrameReceived)
		{
			frame = reinterpret_cast<rage::netConnection::InFrame*>(event);
			if (frame->m_data == nullptr || frame->m_length == 0 || frame->m_connection_identifier == 2)
				return g_hooking->get_original<hooks::receive_net_message>()(a1, net_cxn_mgr, event);

			message_data = frame->m_data;
			message_size = frame->m_length;
		}
		else if (event->get_event_type() == rage::netEvent::Type::ConnectionError)
		{
			error = reinterpret_cast<rage::netEventConnectionError*>(event);
			if (error->m_size == 0)
				return g_hooking->get_original<hooks::receive_net_message>()(a1, net_cxn_mgr, event);

			message_data = error->m_data;
			message_size = error->m_size;
		}
		else
		{
			return g_hooking->get_original<hooks::receive_net_message>()(a1, net_cxn_mgr, event);
		}


		rage::datBitBuffer buffer(message_data, message_size);
		buffer.m_flagBits = 1;

		if (try_read_secondary_header(buffer))
		{
			buffer            = rage::datBitBuffer(((char*)message_data) + 7, message_size - 7);
			buffer.m_flagBits = 1;
		}
		else
		{
			buffer.Seek(0);
		}

		rage::eNetMessage msgType;

		if (!get_msg_type(msgType, buffer))
		{
			//LOGF(stream::net_messages, WARNING, "Received message that we cannot parse from cxn id {}", event->m_connection_identifier);
			return g_hooking->get_original<hooks::receive_net_message>()(a1, net_cxn_mgr, event);
		}

		switch (msgType)
		{
		case rage::eNetMessage::MsgKickPlayer:
		{
			if (g_is_enhanced && !anti_cheat_bypass::is_fsl_providing_be_bypass())
				return false;
			break;
		}
		case rage::eNetMessage::MsgBattlEyeCmd:
		{
			if (g_is_enhanced && !anti_cheat_bypass::is_fsl_providing_be_bypass() && !anti_cheat_bypass::is_battleye_running())
			{
				char data[1028]{};
				int size         = buffer.Read<int>(11);
				bool from_client = buffer.Read<bool>(1);
				buffer.Seek(4); // normalize before we read
				buffer.ReadArrayBytes(&data, size);

				if (from_client)
					break;

				packet reply;
				char reply_buf[1028]{};
				int reply_sz = 0;

				auto op = data[0];

				if (op == 0)
				{
					char payload[] = {0x0, 0x5};
					reply_sz       = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 2 || op == 4)
				{
					char payload[] = {op, data[1]};
					reply_sz       = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 9)
				{
					reply_sz = size;
					memcpy(reply_buf, data, reply_sz);
				}

				reply.write_message(rage::eNetMessage::MsgBattlEyeCmd);
				reply.write<int>(reply_sz, 11);
				reply.write<bool>(true, 1);
				reply.seek(4);
				reply.write_array_bytes(reply_buf, reply_sz);
				reply.send(event->m_msg_id);
			}
			break;
		}
		default: break;
		}

		auto event_ret = g_lua_manager->trigger_event<"ReceiveNetMessage", bool>((uint64_t)a1, (uint64_t)net_cxn_mgr, (uint64_t)event, (uint32_t)msgType, (uint64_t)&buffer);
		if (event_ret.has_value())
			return event_ret.value();


		int sec_id               = 0;
		rage::SecurityPeer* peer = nullptr;

		if (!g_is_enhanced)
		{
			if (frame)
			{
				sec_id = frame->m_security_id;
			}
			else
			{
				if (auto cxn = g_pointers->m_get_connection_peer(net_cxn_mgr, error->m_peer_id))
					sec_id = cxn->m_security_id;
			}

			peer = g_pointers->m_get_peer_by_security_id(sec_id); // shouldn't be null in most cases, contains unspoofable data

			if (error && msgType != rage::eNetMessage::MsgJoinResponse)
			{
				if (peer)
					LOGF(stream::net_messages,
					    WARNING,
					    "Received an error packet that isn't MsgJoinResponse from {}",
					    peer->m_info.name);
				return true;
			}
		}

		if (g.packet_logs)
		{
			log_net_message(msgType, buffer, event, peer);
		}

		return g_hooking->get_original<hooks::receive_net_message>()(a1, net_cxn_mgr, event);
	}
}
