/**
 * @file pointers.cpp
 * @brief All the signature scans are here.
 */

#include "pointers.hpp"

#include "memory/all.hpp"

namespace big
{
	pointers::pointers()
	{
		memory::batch main_batch;

		main_batch.add("Game state", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", [this](memory::handle ptr) {
			m_game_state = ptr.add(2).rip().add(1).as<eGameState*>();
		});

		main_batch.add("Is session started", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", [this](memory::handle ptr) {
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

		main_batch.add("Ped factory", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", [this](memory::handle ptr) {
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});

		main_batch.add("Network player manager", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", [this](memory::handle ptr) {
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});

		main_batch.add("Native handlers", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", [this](memory::handle ptr) {
			m_init_native_tables        = ptr.sub(37).as<PVOID>();
			m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
			m_get_native_handler        = ptr.add(12).rip().as<functions::get_native_handler_t>();
		});

		main_batch.add("Fix vectors", "83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA", [this](memory::handle ptr) {
			m_fix_vectors = ptr.as<functions::fix_vectors_t>();
		});

		main_batch.add("Script threads", "45 33 F6 8B E9 85 C9 B8", [this](memory::handle ptr) {
			m_script_threads     = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
		});

		main_batch.add("Script programs", "48 8B 1D ? ? ? ? 41 83 F8 FF", [this](memory::handle ptr) {
			m_script_program_table = ptr.add(3).rip().as<decltype(m_script_program_table)>();
		});

		main_batch.add("Script globals", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});

		main_batch.add("Script VM", "E8 ? ? ? ? 48 85 FF 48 89 1D", [this](memory::handle ptr) {
			m_script_vm = ptr.add(1).rip().as<functions::script_vm>();
		});

		main_batch.add("CGameScriptHandlerMgr", "48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF", [this](memory::handle ptr) {
			m_script_handler_mgr = ptr.add(3).rip().as<CGameScriptHandlerMgr**>();
		});

		main_batch.add("Swapchain", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", [this](memory::handle ptr) {
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});

		main_batch.add("Model Spawn Bypass", "48 8B C8 FF 52 30 84 C0 74 05 48", [this](memory::handle ptr) {
			m_model_spawn_bypass = ptr.add(8).as<PVOID>();
		});

		main_batch.add("Ptr To Handle", "48 8B F9 48 83 C1 10 33 DB", [this](memory::handle ptr) {
			m_ptr_to_handle = ptr.sub(0x15).as<decltype(m_ptr_to_handle)>();
		});

		main_batch.add("Handle To Ptr", "83 F9 FF 74 31 4C 8B 0D", [this](memory::handle ptr) {
			m_handle_to_ptr = ptr.as<decltype(m_handle_to_ptr)>();
		});

		main_batch.add("Queue Dependency", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B F2 49 8B F8", [this](memory::handle ptr) {
			m_queue_dependency = ptr.as<PVOID>();
		});

		main_batch.add("Game Skeleton", "48 8D 0D ? ? ? ? BA ? ? ? ? 74 05 BA ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8D 0D ? ? ? ? BA ? ? ? ? 84 DB 75 05 BA ? ? ? ? E8 ? ? ? ? 48 8B CD C6 05 ? ? ? ? ? E8 ? ? ? ? 84", [this](memory::handle ptr) {
			m_game_skeleton = ptr.add(3).rip().as<rage::game_skeleton*>();
		});

		main_batch.add("Nullsub", "90 C3 CC", [this](memory::handle ptr) {
			m_nullsub = ptr.as<void (*)()>();
		});

		main_batch.add("Ped Pool", "4C 8B 35 ? ? ? ? B8 ? ? ? ? 0F 57 F6 89 05 ? ? ? ? 49 63 76 10 4C 8B FE 85 F6 0F 84 ? ? ? ? 49 8B 46 08 49 FF CF FF CE 42 0F B6 0C 38", [this](memory::handle ptr) {
			m_ped_pool = ptr.add(3).rip().as<GenericPool**>();
		});

		main_batch.add("Prop Pool", "48 8B 05 ? ? ? ? 0F B7 50 10 48 8B 05", [this](memory::handle ptr) {
			m_prop_pool = ptr.add(3).rip().as<GenericPool**>();
		});

		main_batch.add("Vehicle Pool", "4C 8B 25 ? ? ? ? 8B 29 33 F6 49 8B 04 24 33 DB 4C 8D 71 08 44 8B 78 08 45 85 FF 0F 8E ? ? ? ? 4D 8B 0C 24 41 3B 59 08 7D 29 49 8B 51 30 44 8B C3 8B CB 49 C1 E8 05 83 E1 1F 44 8B D3 42 8B 04 82", [this](memory::handle ptr) {
			m_vehicle_pool = ptr.add(3).rip().as<VehiclePool***>();
		});

		main_batch.add("Network", "48 8B 0D ? ? ? ? 45 33 C9 48 8B D7", [this](memory::handle ptr) {
			m_network = ptr.add(3).rip().as<Network**>();
		});

		main_batch.add("Get Connection Peer", "48 89 5C 24 08 48 89 74 24 18 89 54 24 10 57 48 83 EC 40 48", [this](memory::handle ptr) {
			m_get_connection_peer = ptr.as<functions::get_connection_peer>();
		});

		main_batch.add("Send Network Damage", "E8 ? ? ? ? E9 E9 01 00 00 48 8B CB", [this](memory::handle ptr) {
			m_send_network_damage = ptr.add(1).rip().as<functions::send_network_damage>();
		});

		main_batch.add("Give Pickup Reward", "48 8B C8 33 C0 48 85 C9 74 0A 44 8B C3 8B D7 E8", [this](memory::handle ptr) {
			m_give_pickup_rewards = ptr.sub(0x28).as<decltype(m_give_pickup_rewards)>();
		});

		main_batch.add("Trigger Script Event", "48 8B C4 48 89 58 08 44 89 48 20 55 56 57 48 83 EC 30", [this](memory::handle ptr) {
			m_trigger_script_event = ptr.as<decltype(pointers::m_trigger_script_event)>();
		});

		main_batch.add("Received Event Hook", "66 41 83 F9 ? 0F 83", [this](memory::handle ptr) {
			m_received_event = ptr.as<decltype(pointers::m_received_event)>();
		});

		main_batch.add("Send Event Acknowledge", "E8 ? ? ? ? 66 83 7B 08 5B", [this](memory::handle ptr) {
			m_send_event_ack = ptr.add(1).rip().as<decltype(pointers::m_send_event_ack)>();
		});

		main_batch.add("Read Bitbuffer WORD/DWORD", "48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A", [this](memory::handle ptr) {
			m_read_bitbuf_dword = ptr.sub(5).as<decltype(pointers::m_read_bitbuf_dword)>();
		});

		main_batch.add("Read Bitbuffer Array", "48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C", [this](memory::handle ptr) {
			m_read_bitbuf_array = ptr.as<decltype(pointers::m_read_bitbuf_array)>();
		});

		main_batch.add("Read Bitbuffer String", "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48 83 EC 20 48 8B F2 45", [this](memory::handle ptr) {
			m_read_bitbuf_string = ptr.as<decltype(pointers::m_read_bitbuf_string)>();
		});

		main_batch.add("Read Bitbuffer Boolean", "48 8B C4 48 89 58 08 55 56 57 48 83 EC 20 48 83 60", [this](memory::handle ptr) {
			m_read_bitbuf_bool = ptr.as<decltype(pointers::m_read_bitbuf_bool)>();
		});

		main_batch.add("Write Bitbuffer WORD/DWORD", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 8B EA BF 01", [this](memory::handle ptr) {
			m_write_bitbuf_dword = ptr.as<decltype(pointers::m_write_bitbuf_dword)>();
		});

		main_batch.add("Write Bitbuffer QWORD", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20", [this](memory::handle ptr) {
			m_write_bitbuf_qword = ptr.as<decltype(pointers::m_write_bitbuf_qword)>();
		});

		main_batch.add("Write Bitbuffer Int64", "E8 ? ? ? ? 8A 53 39 48 8B CF", [this](memory::handle ptr) {
			m_write_bitbuf_int64 = ptr.add(1).rip().as<decltype(pointers::m_write_bitbuf_int64)>();
		});

		main_batch.add("Write Bitbuffer Int32", "E8 ? ? ? ? 8A 53 74", [this](memory::handle ptr) {
			m_write_bitbuf_int32 = ptr.add(1).rip().as<decltype(pointers::m_write_bitbuf_int32)>();
		});

		main_batch.add("Write Bitbuffer Boolean", "E8 ? ? ? ? 8A 57 39", [this](memory::handle ptr) {
			m_write_bitbuf_bool = ptr.add(1).rip().as<decltype(pointers::m_write_bitbuf_bool)>();
		});

		main_batch.add("Write Bitbuffer Array", "E8 ? ? ? ? 01 7E 08", [this](memory::handle ptr) {
			m_write_bitbuf_array = ptr.add(1).rip().as<decltype(pointers::m_write_bitbuf_array)>();
		});

		main_batch.add("World Model Spawn Bypass", "48 85 C0 0F 84 ? ? ? ? 8B 48 50", [this](memory::handle ptr) {
			m_world_model_spawn_bypass = ptr.as<PVOID>();
		});

		main_batch.add("Blame Explode", "0F 85 EE 00 00 00 84 C0", [this](memory::handle ptr) {
			m_blame_explode = ptr;
		});

		main_batch.add("Patch blocked explosions", "E8 ? ? ? ? 48 8D 4C 24 20 E8 ? ? ? ? 4C 8D 9C 24 80 01 00 00", [this](memory::handle ptr) {
			m_explosion_patch = ptr;
		});

		main_batch.add("Queue Packet", "E8 ? ? ? ? 84 C0 74 4D B3 01", [this](memory::handle ptr) {
			m_queue_packet = ptr.add(1).rip().as<functions::queue_packet>();
		});

		main_batch.add("Send Packet", "48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 48 20 55 41 54 41 55 41 56 41 57 48 8D A8 98", [this](memory::handle ptr) {
			m_send_packet = ptr.as<functions::send_packet>();
		});

		// Received clone sync & Get sync tree for type & Get net object for player & Get sync type info & Get net object
		main_batch.add("RCS/GSTFT/GNOFP/GNO/GSTI", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 40 4C 8B EA", [this](memory::handle ptr) {
			m_received_clone_sync = ptr.as<decltype(pointers::m_received_clone_sync)>();
			m_get_sync_tree_for_type = ptr.add(0x2F).add(1).rip().as<decltype(pointers::m_get_sync_tree_for_type)>(); // 0F B7 CA 83 F9 07 .as()
			m_get_net_object = ptr.add(0x109).add(1).rip().as<decltype(pointers::m_get_net_object)>(); // E8 ? ? ? ? 0F B7 53 7C .add(1).rip().as()
			m_get_sync_type_info = ptr.add(0x11F).add(1).rip().as<decltype(pointers::m_get_sync_type_info)>(); // 44 0F B7 C1 4C 8D 0D .as()
		});

		main_batch.add("GET_GAMEPLAY_CAM_COORDS", "8B 90 ? ? ? ? 89 13", [this](memory::handle ptr) {
			m_get_gameplay_cam_coords = ptr.sub(0xE).as<functions::get_gameplay_cam_coords>();
		});

		main_batch.add("Request Control", "E8 ? ? ? ? EB 50 48 8B D3", [this](memory::handle ptr) {
			m_request_control = ptr.add(1).rip().as<functions::request_control>();
		});

		main_batch.add("CNetworkObjectMgr", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", [this](memory::handle ptr) {
			m_network_object_mgr = ptr.add(3).rip().as<CNetworkObjectMgr**>();
		});

		main_batch.add("Receive Net Message", "48 83 EC 20 4C 8B 71 50 33 ED", [this](memory::handle ptr) {
			m_receive_net_message = ptr.sub(0x19).as<PVOID>();
		});

		main_batch.add("Get Network Event Data", "53 43 52 49 50 54 5F 4E 45 54 57 4F 52 4B", [this](memory::handle ptr) {
			m_get_network_event_data = *ptr.sub(0x38).as<PVOID*>();
		});

		main_batch.add("Assign Physical Index", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8", [this](memory::handle ptr) {
			m_assign_physical_index = ptr.as<PVOID>();
		});

		main_batch.add("Network Player Mgr Init", "41 56 48 83 EC ? 48 8B F1 B9 ? ? ? ? 49 8B F9 41 8B E8 4C 8B F2 E8", [this](memory::handle ptr) {
			m_network_player_mgr_init = ptr.sub(0x13).as<decltype(pointers::m_network_player_mgr_init)>();
		});

		main_batch.add("Network Player Mgr Shutdown", "48 8D 9F ? ? ? ? EB ? 48 8B 13 48 85 D2 74 ? 48 8B CB E8 ? ? ? ? 48 83 7B ? ? 75 ? 48 8D 9F", [this](memory::handle ptr) {
			m_network_player_mgr_shutdown = ptr.sub(0x1A).as<decltype(pointers::m_network_player_mgr_shutdown)>();
		});

		main_batch.add("Network Can Access Multiplayer", "E9 36 01 00 00 33 D2 8B CB", [this](memory::handle ptr) {
			m_network_can_access_multiplayer = ptr.add(10).rip().as<PVOID>();
		});

		main_batch.add("Terminate Game", "E8 ? ? ? ? EB 14 41 83", [this](memory::handle ptr) {
			// Multiple results but they all point to the same function.
			m_terminate_game = ptr.add(1).rip().as<PVOID>();
		});

		main_batch.add("Update Script Threads", "40 53 48 83 EC 30 48 8D 0D ? ? ? ? E8 ? ? ? ? 48", [this](memory::handle ptr) {
			m_update_script_threads = ptr.as<PVOID>();
		});

		main_batch.add("Add plane lift", "F3 44 0F 11 74 24 20 ? ? ? ? ? 41 0F 28 D7", [this](memory::handle ptr) {
			m_add_plane_lift = ptr.add(8).rip().as<PVOID>();
			m_apply_plane_thrust = ptr.sub(0x3FA).rip().as<PVOID>();
		});

		main_batch.run(memory::module(""));

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
