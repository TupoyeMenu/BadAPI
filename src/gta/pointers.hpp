#pragma once
#include "function_types.hpp"
#include "gta/enums.hpp"
#include "gta/fwddec.hpp"
#include "memory/byte_patch.hpp"

#include <memory/handle.hpp>
#include <player/CPlayerInfo.hpp>

namespace big
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();

	public:
		HWND m_hwnd{};

		eGameState* m_game_state{};
		bool* m_is_session_started{};

		rage::game_skeleton* m_game_skeleton{};
		void (*m_nullsub)(){};

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};

		rage::scrNativeRegistrationTable* m_native_registration_table{};
		PVOID m_unk_native{};

		rage::atArray<rage::scrThread*>* m_script_threads{};
		rage::scrProgramTable* m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t** m_script_globals{};
		PVOID m_init_native_tables{};
		functions::script_vm m_script_vm{};

		CGameScriptHandlerMgr** m_script_handler_mgr{};

		IDXGISwapChain** m_swapchain{};
		ID3D12CommandQueue** m_command_queue{};

		uint32_t* m_resolution_x{};
		uint32_t* m_resolution_y{};

		memory::byte_patch* m_model_spawn_bypass{};

		functions::ptr_to_handle m_ptr_to_handle{};
		functions::handle_to_ptr m_handle_to_ptr{};

		PVOID m_queue_dependency{};
		PVOID m_sig_scan_memory{};

		void** m_ped_pool{};
		void** m_prop_pool{};
		void*** m_vehicle_pool{};

		Network** m_network{};

		functions::get_connection_peer m_get_connection_peer{};

		functions::give_pickup_rewards m_give_pickup_rewards{};
		functions::send_network_damage m_send_network_damage{};

		memory::handle m_explosion_patch{};

		functions::queue_packet m_queue_packet{};

		//Sync Signatures START
		PVOID m_received_clone_sync{};
		functions::get_sync_tree_for_type m_get_sync_tree_for_type{};
		functions::get_sync_type_info m_get_sync_type_info{};
		functions::get_net_object m_get_net_object{};
		functions::get_net_object_by_id m_get_net_object_by_id{};
		//Sync Signatures END

		functions::get_gameplay_cam_coords m_get_gameplay_cam_coords{};

		functions::request_control m_request_control{};

		CNetworkObjectMgr** m_network_object_mgr{};

		PVOID m_receive_net_message{};
		PVOID m_assign_physical_index{};

		PVOID m_network_player_mgr_init{};
		PVOID m_network_player_mgr_shutdown{};

		PVOID m_terminate_game{};

		PVOID m_handle_join_request{};
		functions::write_join_response_data m_write_join_response_data{};
		functions::get_peer_by_security_id m_get_peer_by_security_id{};

		functions::print_script_stack_trace m_print_script_stack_trace{};

		int* m_be_restart_status{};
		bool* m_needs_be_restart{};
		bool* m_is_be_banned{};

		PVOID m_prepare_metric_for_sending{};

		PVOID m_gta_thread_vtable{};

		rage::sysMemAllocator* m_allocator{};

		PVOID m_gta_thread_create{};
		PVOID m_gta_thread_kill{};
	};

	inline pointers* g_pointers{};
}
