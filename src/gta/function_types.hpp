#pragma once
#include "gta/fwddec.hpp"
#include <script/scrNativeHandler.hpp>

namespace big::functions
{
	using run_script_threads_t = bool (*)(std::uint32_t ops_to_execute);
	using get_native_handler_t = rage::scrNativeHandler (*)(rage::scrNativeRegistrationTable*, rage::scrNativeHash);
	using fix_vectors_t        = void (*)(rage::scrNativeCallContext*);
	using script_vm = rage::eThreadState (*)(uint64_t* stack, int64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx);

	using ptr_to_handle = Entity (*)(void*);
	using handle_to_ptr = rage::CDynamicEntity* (*)(Entity);

	using get_connection_peer = rage::netConnectionPeer* (*)(rage::netConnectionManager* manager, int peer_id);

	using give_pickup_rewards = void (*)(int players, uint32_t hash);
	using send_network_damage = void (*)(rage::CEntity* source, rage::CEntity* target, rage::fvector3* position, int hit_component, bool override_default_damage, int weapon_type, float override_damage, int tire_index, int suspension_index, int flags, uint32_t action_result_hash, int16_t action_result_id, int action_unk, bool hit_weapon, bool hit_weapon_ammo_attachment, bool silenced, bool unk, rage::fvector3* impact_direction);

	using trigger_script_event = void (*)(int event_group, int64_t* args, int arg_count, int player_bits, int event_id);

	// Bitbuffer read/write START
	using read_bitbuf_dword  = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits);
	using read_bitbuf_string = bool (*)(rage::datBitBuffer* buffer, char* read, int bits);
	using read_bitbuf_bool   = bool (*)(rage::datBitBuffer* buffer, bool* read, int bits);
	using read_bitbuf_array  = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using write_bitbuf_qword = bool (*)(rage::datBitBuffer* buffer, uint64_t val, int bits);
	using write_bitbuf_dword = bool (*)(rage::datBitBuffer* buffer, uint32_t val, int bits);
	using write_bitbuf_int64 = bool (*)(rage::datBitBuffer* buffer, int64_t val, int bits);
	using write_bitbuf_int32 = bool (*)(rage::datBitBuffer* buffer, int32_t val, int bits);
	using write_bitbuf_bool  = bool (*)(rage::datBitBuffer* buffer, bool val, int bits);
	using write_bitbuf_array = bool (*)(rage::datBitBuffer* buffer, void* val, int bits, int unk);

	// Bitbuffer read/write END
	// Received Event Signatures START
	using send_event_ack = void (*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);
	// Received Event Signatures END

	using queue_packet = bool (*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, void* unk);
	using send_packet = bool (*)(rage::netConnectionManager* mgr, rage::netPeerAddress* adde, int connection_id, void* data, int size, int flags);

	//Sync signatures START
	using get_sync_type_info = const char* (*)(uint16_t sync_type, char a2);

	using get_sync_tree_for_type = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);

	using get_net_object = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);

	using get_net_object_for_player = rage::netObject* (*)(CNetworkObjectMgr*, int16_t, CNetGamePlayer*, bool);

	using read_bitbuffer_into_sync_tree = void (*)(rage::netSyncTree* tree, uint64_t flag, uint32_t flag2, rage::datBitBuffer* buffer, uint64_t netLogStub);
	//Sync signatures END

	using get_gameplay_cam_coords = Vector3 (*)();

	using request_control = void (*)(rage::netObject* net_object);
}
