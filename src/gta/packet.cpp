#include "packet.hpp"

#include "gta/fwddec.hpp"
#include "gta/gta_util.hpp"
#include "gta/pointers.hpp"

#include <network/Network.hpp>
#include <network/netConnection.hpp>

namespace big
{
	packet::packet() :
	    m_buffer(m_data, sizeof(m_data))
	{
	}

	void packet::send(uint32_t msg_id, bool unk_flag)
	{
		// TODO: add a name for pad_0008
		g_pointers->m_queue_packet((rage::netConnectionManager*)(*g_pointers->m_network_player_mgr)->pad_0008, msg_id, m_data, (m_buffer.m_curBit + 7) >> 3, unk_flag ? 0x4000001 : 1, nullptr);
	}
}