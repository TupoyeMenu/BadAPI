/**
 * @file pointers.cpp
 * @brief All the signature scans are here.
 */

#include "pointers.hpp"

#include "common.hpp"
#include "gta/function_types.hpp"
#include "memory/all.hpp"
#include <string>

namespace big
{
	pointers::pointers()
	{
		memory::batch early_batch;

		early_batch.add("Game Version", "8B C3 33 D2 C6 44 24 20", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			g_game_version = std::stoi(ptr.add(0x24).rip().as<const char*>());
		});
		early_batch.add("Game Version", "4C 8D 0D ? ? ? ? 48 8D 5C 24 ? 48 89 D9 48", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			g_game_version = std::stoi(ptr.add(3).rip().as<const char*>());
		});

		early_batch.run(memory::module(""));

		memory::batch main_batch;

		main_batch.add("Screen Resolution", "66 0F 6E 0D ? ? ? ? 0F B7 3D", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_resolution_x = ptr.sub(4).rip().as<uint32_t*>();
			m_resolution_y = ptr.add(4).rip().as<uint32_t*>();
		});
		main_batch.add("Screen Resolution", "75 39 0F 57 C0 F3 0F 2A 05", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_resolution_x = ptr.add(0x5).add(4).rip().as<uint32_t*>();
			m_resolution_y = ptr.add(0x1E).add(4).rip().as<uint32_t*>();
		});

		main_batch.add("Is session started", "40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});
		main_batch.add("Is session started", "0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_is_session_started = ptr.add(3).rip().as<bool*>();
		});

		main_batch.add("Game state", "83 3D ? ? ? ? ? 75 17 8B 43 20 25", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_game_state = ptr.add(2).rip().add(1).as<eGameState*>();
		});
		main_batch.add("Game state", "83 3D ? ? ? ? ? 0F 85 ? ? ? ? BA ? 00", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_game_state = ptr.add(2).rip().add(1).as<eGameState*>();
		});

		main_batch.add("Ped factory", "48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_ped_factory = ptr.add(3).rip().as<CPedFactory**>();
		});
		main_batch.add("Ped factory", "C7 40 30 03 00 00 00 48 8B 0D", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_ped_factory = ptr.add(7).add(3).rip().as<CPedFactory**>();
		});

		main_batch.add("Network player manager", "48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_network_player_mgr = ptr.add(3).rip().as<CNetworkPlayerMgr**>();
		});
		main_batch.add("Network player manager", "75 0E 48 8B 05 ? ? ? ? 48 8B 88 F0 00 00 00", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_network_player_mgr = ptr.add(2).add(3).rip().as<CNetworkPlayerMgr**>();
		});


		main_batch.add("Native handlers", "48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_init_native_tables        = ptr.sub(37).as<PVOID>();
			m_native_registration_table = ptr.add(3).rip().as<rage::scrNativeRegistrationTable*>();
			m_unk_native                = ptr.add(24).rip().as<PVOID>();
		});
		main_batch.add("Native handlers", "EB 2A 0F 1F 40 00 48 8B 54 17 10", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_init_native_tables        = ptr.sub(0x2A).as<PVOID>();
			m_native_registration_table = ptr.sub(0xE).rip().as<rage::scrNativeRegistrationTable*>();
			m_unk_native                = ptr.sub(7).rip().as<PVOID>();
		});

		main_batch.add("Script threads", "45 33 F6 8B E9 85 C9 B8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_script_threads     = ptr.sub(4).rip().sub(8).as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0x1F).as<functions::run_script_threads_t>();
		});
		main_batch.add("Script threads", "BE 40 5D C6 00", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_script_threads     = ptr.add(0x1B).rip().as<decltype(m_script_threads)>();
			m_run_script_threads = ptr.sub(0xA).as<functions::run_script_threads_t>();
		});

		main_batch.add("Script programs", "48 8B 1D ? ? ? ? 41 83 F8 FF", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_script_program_table = ptr.add(3).rip().as<decltype(m_script_program_table)>();
		});
		main_batch.add("Script programs", "89 46 38 48 8B 0D ? ? ? ? 0F", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_script_program_table = ptr.add(0x16).rip().as<decltype(m_script_program_table)>();
		});

		main_batch.add("Script globals", "48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_script_globals = ptr.add(3).rip().as<std::int64_t**>();
		});
		main_batch.add("Script globals", "48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_script_globals = ptr.add(10).rip().as<std::int64_t**>();
		});

		main_batch.add("Script VM", "E8 ? ? ? ? 48 85 FF 48 89 1D", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_script_vm = ptr.add(1).rip().as<functions::script_vm>();
		});
		main_batch.add("Script VM", "49 63 41 1C", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_script_vm = ptr.sub(0x24).as<functions::script_vm>();
		});

		main_batch.add("Swapchain", "48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_swapchain = ptr.add(3).rip().as<IDXGISwapChain**>();
		});
		main_batch.add("Swapchain", "72 C7 EB 02 31 C0 8B 0D", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_command_queue = ptr.add(0x1A).add(3).rip().as<ID3D12CommandQueue**>();
			m_swapchain     = ptr.add(0x21).add(3).rip().as<IDXGISwapChain**>();
		});

		main_batch.add("Model Spawn Bypass", "48 8B C8 FF 52 30 84 C0 ? 05 48", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_model_spawn_bypass =
			    memory::byte_patch::make(ptr.add(8).as<PVOID>(), std::to_array<uint8_t>({0x90, 0x90})).get();
		});
		main_batch.add("Model Spawn Bypass", "E8 ? ? ? ? 48 8B 78 48", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_model_spawn_bypass = memory::byte_patch::make(ptr.add(1).rip().add(0x2B).as<uint8_t*>(), 0xEB).get();
		});

		main_batch.add("Ptr To Handle", "48 8B F9 48 83 C1 10 33 DB", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_ptr_to_handle = ptr.sub(0x15).as<decltype(m_ptr_to_handle)>();
		});
		main_batch.add("Handle To Ptr", "83 F9 FF 74 31 4C 8B 0D", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_handle_to_ptr = ptr.as<decltype(m_handle_to_ptr)>();
		});
		main_batch.add("HandlesAndPtrs", "0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE 41", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_handle_to_ptr = ptr.add(0x21).add(1).rip().as<decltype(m_handle_to_ptr)>();
			m_ptr_to_handle = ptr.sub(0xB).add(1).rip().as<decltype(m_ptr_to_handle)>();
		});

		main_batch.add("Queue Dependency", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 8B F2 49 8B F8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_queue_dependency = ptr.as<PVOID>();
		});
		main_batch.add("Queue Dependency", "0F 29 46 50 48 8D 05", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_queue_dependency = ptr.add(0x71).add(1).rip().as<PVOID>();
			m_sig_scan_memory  = ptr.add(4).add(3).rip().as<PVOID>();
		});

		main_batch.add("Game Skeleton", "48 8D 0D ? ? ? ? BA ? ? ? ? 74 05 BA ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? ? 48 8D 0D ? ? ? ? BA ? ? ? ? 84 DB 75 05 BA ? ? ? ? E8 ? ? ? ? 48 8B CD C6 05 ? ? ? ? ? E8 ? ? ? ? 84", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_game_skeleton = ptr.add(3).rip().as<rage::game_skeleton*>();
		});

		main_batch.add("Nullsub", "90 C3 CC", [this](memory::handle ptr) {
			m_nullsub = ptr.as<void (*)()>();
		});

		main_batch.add("Ped Pool", "4C 8B 35 ? ? ? ? B8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_ped_pool = ptr.add(3).rip().as<void**>();
		});
		main_batch.add("Ped Pool", "80 79 4B 00 0F 84 F5 00 00 00 48 89 F1", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_ped_pool = ptr.add(0x18).add(3).rip().as<void**>();
		});

		main_batch.add("Prop Pool", "48 8B 05 ? ? ? ? 0F B7 50 10 48 8B 05", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_prop_pool = ptr.add(3).rip().as<void**>();
		});
		main_batch.add("Prop Pool", "48 8B 04 0A C3 0F B6 05", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_prop_pool = ptr.add(5).add(3).rip().as<void**>();
		});

		main_batch.add("Vehicle Pool", "4C 8B 25 ? ? ? ? 8B 29", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_vehicle_pool = ptr.add(3).rip().as<void***>();
		});
		main_batch.add("Vehicle Pool", "48 83 78 18 0D", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_vehicle_pool = ptr.sub(0xA).add(3).rip().as<void***>();
		});

		main_batch.add("Network", "48 8B 0D ? ? ? ? 45 33 C9 48 8B D7", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_network = ptr.add(3).rip().as<Network**>();
		});
		main_batch.add("Network", "49 C7 86 F8 00 00 00 00 00 00 00 48 8B 05", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_network = ptr.add(0x17).add(3).rip().as<Network**>();
		});

		main_batch.add("Get Connection Peer", "48 89 5C 24 08 48 89 74 24 18 89 54 24 10 57 48 83 EC 40 48", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_get_connection_peer = ptr.as<functions::get_connection_peer>();
		});
		// FIXME: inline on enhanced

		main_batch.add("Send Network Damage", "E8 ? ? ? ? E9 E9 01 00 00 48 8B CB", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_send_network_damage = ptr.add(1).rip().as<functions::send_network_damage>();
		});
		main_batch.add("Send Network Damage", "0F B6 41 28 04 FE 3C 03 0F 87 EA", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_send_network_damage = ptr.sub(0x51).as<functions::send_network_damage>();
		});

		main_batch.add("Give Pickup Reward", "48 8B C8 33 C0 48 85 C9 74 0A 44 8B C3 8B D7 E8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_give_pickup_rewards = ptr.sub(0x28).as<decltype(m_give_pickup_rewards)>();
		});
		main_batch.add("Give Pickup Reward", "8B 53 08 89 F9 E8 ? ? ? ? E9", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_give_pickup_rewards = ptr.add(6).rip().as<decltype(m_give_pickup_rewards)>();
		});

		main_batch.add("Blame Explode", "0F 85 EE 00 00 00 84 C0", -1, 3521, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_blame_explode = ptr;
		});
		main_batch.add("Blame Explode", "0F 85 EF 00 00 00 84 C0", 3570, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_blame_explode = ptr;
		});
		main_batch.add("Blame Explode", "0F 85 d3 00 00 00 84", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_blame_explode = ptr;
		});

		main_batch.add("Patch blocked explosions", "E8 ? ? ? ? 48 8D 4C 24 20 E8 ? ? ? ? 4C 8D 9C 24 80 01 00 00", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_explosion_patch = ptr.sub(12);
		});
		main_batch.add("Patch blocked explosions", "81 7C 24 30 D0 1A 46 BF", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_explosion_patch = ptr.add(8);
		});

		main_batch.add("Queue Packet", "E8 ? ? ? ? 84 C0 74 4D B3 01", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_queue_packet = ptr.add(1).rip().as<functions::queue_packet>();
		});
		main_batch.add("Queue Packet", "45 89 F1 E8 ? ? ? ? 84 C0 74 25", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_queue_packet = ptr.add(4).rip().as<functions::queue_packet>();
		});

		// Received clone sync & Get sync tree for type & Get net object for player & Get sync type info & Get net object
		main_batch.add("RCS/GSTFT/GNOFP/GNO/GSTI", "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 40 4C 8B EA", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_received_clone_sync = ptr.as<decltype(pointers::m_received_clone_sync)>();
			m_get_sync_tree_for_type = ptr.add(0x2F).add(1).rip().as<decltype(pointers::m_get_sync_tree_for_type)>(); // 0F B7 CA 83 F9 07 .as()
			m_get_net_object = ptr.add(0x109).add(1).rip().as<decltype(pointers::m_get_net_object)>(); // E8 ? ? ? ? 0F B7 53 7C .add(1).rip().as()
			m_get_sync_type_info = ptr.add(0x11F).add(1).rip().as<decltype(pointers::m_get_sync_type_info)>(); // 44 0F B7 C1 4C 8D 0D .as()
		});
		main_batch.add("Get Net Object By Id", "0F B7 4E 60 E8", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_get_net_object_by_id = ptr.add(5).rip().as<functions::get_net_object_by_id>();
		});

		main_batch.add("Request Control", "E8 ? ? ? ? EB 50 48 8B D3", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_request_control = ptr.add(1).rip().as<functions::request_control>();
		});
		main_batch.add("Request Control", "74 0A 48 89 F9 E8 ? ? ? ? 31 F6 89 F0 48 83 C4 20", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_request_control = ptr.add(6).rip().as<functions::request_control>();
		});

		main_batch.add("CNetworkObjectMgr", "48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_network_object_mgr = ptr.add(3).rip().as<CNetworkObjectMgr**>();
		});
		main_batch.add("CNetworkObjectMgr", "41 83 7E FA 02 40 0F 9C C5 C1 E5 02", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_network_object_mgr     = ptr.add(0xC).add(3).rip().as<CNetworkObjectMgr**>();
			m_get_sync_tree_for_type = ptr.add(0x13).add(1).rip().as<decltype(pointers::m_get_sync_tree_for_type)>();
		});

		main_batch.add("Receive Net Message", "48 83 EC 20 4C 8B 71 50 33 ED", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_receive_net_message = ptr.sub(0x19).as<PVOID>();
		});
		main_batch.add("Receive Net Message", "48 81 C1 00 03 00 00 4C 89 E2", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_receive_net_message = ptr.add(0xD).add(1).rip().as<PVOID>();
		});

		main_batch.add("Assign Physical Index", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_assign_physical_index = ptr.as<PVOID>();
		});
		main_batch.add("Assign Physical Index", "41 8D 47 01 3C 20 0F 87 68 01 00 00", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_assign_physical_index = ptr.sub(0x13).as<PVOID>();
		});

		main_batch.add("Network Player Mgr Init", "57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B F1 B9 07 00 00 00", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_network_player_mgr_init = ptr.sub(0x13).as<decltype(pointers::m_network_player_mgr_init)>();
		});
		main_batch.add("Network Player Mgr Init", "4C 89 CF 45 89 C6 48 89 D3 48 89 CE B9", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_network_player_mgr_init = ptr.sub(10).as<decltype(pointers::m_network_player_mgr_init)>();
		});

		main_batch.add("Network Player Mgr Shutdown", "48 8D 9F ? ? ? ? EB ? 48 8B 13 48 85 D2 74 ? 48 8B CB E8 ? ? ? ? 48 83 7B ? ? 75 ? 48 8D 9F", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_network_player_mgr_shutdown = ptr.sub(0x1A).as<decltype(pointers::m_network_player_mgr_shutdown)>();
		});
		main_batch.add("Network Player Mgr Shutdown", "84 C0 0F 84 88 00 00 00 4C 89 F9 E8", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_network_player_mgr_shutdown = ptr.sub(0x1B).as<decltype(pointers::m_network_player_mgr_shutdown)>();
		});

		main_batch.add("Terminate Game", "E8 ? ? ? ? EB 14 41 83", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			// Multiple results but they all point to the same function.
			m_terminate_game = ptr.add(1).rip().as<PVOID>();
		});

		main_batch.add("Handle Join Request", "48 8B C4 48 89 58 08 4C 89 48 20 4C 89 40 18 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 18", -1, 3521, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_handle_join_request = ptr.as<PVOID>();
		});
		main_batch.add("Handle Join Request", "4C 8B F1 45 33 ED 48 8D 4D", 3570, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_handle_join_request = ptr.sub(0x2D).as<PVOID>();
		});

		main_batch.add("Write Join Response Data", "E8 ? ? ? ? 41 8B DF 84 C0 74 06", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_write_join_response_data = ptr.add(1).rip().as<functions::write_join_response_data>();
		});

		main_batch.add("Get Peer By Security Id", "76 E0 8B 4C 24 30 E8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_get_peer_by_security_id = ptr.add(7).rip().as<functions::get_peer_by_security_id>();
		});

		main_batch.add("Print Script Stack Trace", "48 89 0D ? ? ? ? 48 8B C8 E8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_print_script_stack_trace = ptr.add(11).rip().as<decltype(pointers::m_print_script_stack_trace)>();
		});
		main_batch.add("Print Script Stack Trace", "48 8D 15 ? ? ? ? 48 89 C1 E8 ? ? ? ? 48 C7 05", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_print_script_stack_trace = ptr.add(11).rip().as<decltype(pointers::m_print_script_stack_trace)>();
		});

		main_batch.add("BE Data", "48 C7 05 ? ? ? ? 00 00 00 00 E8 ? ? ? ? 48 89 C1 E8 ? ? ? ? E8 ? ? ? ? BD 0A 00 00 00", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_be_restart_status = ptr.add(3).rip().add(8).add(4).as<int*>();
			m_needs_be_restart  = ptr.add(3).rip().add(8).add(4).add(8).as<bool*>();
			m_is_be_banned      = ptr.add(3).rip().add(8).add(4).add(8).add(4).as<bool*>();
		});
		main_batch.add("BattlEye Status Update Patch", "80 B9 92 0A 00 00 01", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_battleye_status_update_patch = ptr.sub(0x26).as<uint8_t*>();
		});

		main_batch.add("Prepare Metric For Sending", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 49 8B F0 4C", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_prepare_metric_for_sending = ptr.as<PVOID>();
		});
		main_batch.add("Prepare Metric For Sending", "48 89 F9 FF 50 20 48 8D 15", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_prepare_metric_for_sending = ptr.sub(0x26).as<PVOID>();
		});
		
		main_batch.add("Gta Thread Vtable", "48 83 A3 ? ? ? 00 00 48 8D 05 ? ? ? ? 48 8B CB 48 89 03 E8", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_gta_thread_vtable = ptr.add(11).rip().as<PVOID>();
		});
		main_batch.add("Gta Thread Vtable", "89 F3 31 FF 4C 8D 25", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_gta_thread_vtable = ptr.add(7).rip().as<PVOID>();
		});

		main_batch.add("Natives Registered", "48 8B CB 40 88 2D ? ? ? ? 48", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_natives_registered = ptr.add(6).rip().as<bool*>();
		});
		main_batch.add("Natives Registered", "C6 05 ? ? ? ? ? 48 89 F1 0F 28 74", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_natives_registered = ptr.add(3).rip().as<bool*>();
		});

		main_batch.add("tlsContext allocator offset", "4C 8B C2 B9", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			// Multiple results but they all point to the same offset.
			offsets::tls_context_allocator_offset = *ptr.add(4).as<uint32_t*>();
		});
		main_batch.add("tlsContext allocator offset", "48 8B 04 C1 48 8B 88 ? ? ? ? 48 8B 01 48 8B 40 40 48", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			offsets::tls_context_allocator_offset = *ptr.add(8).as<uint32_t*>();
		});

		main_batch.add("tlsContext thread offset", "48 8B F9 E8 ? ? ? ? FF 47", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			offsets::tls_context_thread_offset = *ptr.add(4).rip().add(16).as<uint32_t*>();
		});
		main_batch.add("tlsContext thread offset", "E8 ? ? ? ? 4C 8B B0 ? ? ? ? 40", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			offsets::tls_context_thread_offset = *ptr.add(1).rip().add(22).as<uint32_t*>();
		});

		main_batch.add("Allocator", "48 8D 1D ? ? ? ? A8 08", -1, -1, eGameBranch::Legacy, [this](memory::handle ptr) {
			m_allocator = ptr.add(3).rip().as<rage::sysMemAllocator*>();
		});
		main_batch.add("Allocator", "48 8D 3D ? ? ? ? 48 89 F9 BA 07", -1, -1, eGameBranch::Enhanced, [this](memory::handle ptr) {
			m_allocator = ptr.add(3).rip().as<rage::sysMemAllocator*>();
		});

		main_batch.run(memory::module(""));

		LPCWSTR lpClassName = g_is_enhanced ? L"sgaWindow" : L"grcWindow";
		m_hwnd              = FindWindowW(lpClassName, nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
