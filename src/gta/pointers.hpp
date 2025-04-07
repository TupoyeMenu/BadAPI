#pragma once
#include "function_types.hpp"
#include "gta/enums.hpp"
#include "gta/fwddec.hpp"

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

		rage::game_skeleton* m_game_skeleton;
		void (*m_nullsub)();

		CPedFactory** m_ped_factory{};
		CNetworkPlayerMgr** m_network_player_mgr{};

		rage::scrNativeRegistrationTable* m_native_registration_table{};
		functions::get_native_handler_t m_get_native_handler{};
		functions::fix_vectors_t m_fix_vectors{};

		rage::atArray<GtaThread*>* m_script_threads{};
		rage::scrProgramTable* m_script_program_table{};
		functions::run_script_threads_t m_run_script_threads{};
		std::int64_t** m_script_globals{};
		PVOID m_init_native_tables{};
		functions::script_vm m_script_vm{};

		CGameScriptHandlerMgr** m_script_handler_mgr{};

		IDXGISwapChain** m_swapchain{};

		PVOID m_model_spawn_bypass;

		functions::ptr_to_handle m_ptr_to_handle{};
		functions::handle_to_ptr m_handle_to_ptr{};

		PVOID m_queue_dependency;

		GenericPool** m_ped_pool;
		GenericPool** m_prop_pool;
		VehiclePool*** m_vehicle_pool;

		Network** m_network;

		functions::get_connection_peer m_get_connection_peer;

		functions::give_pickup_rewards m_give_pickup_rewards;
		functions::send_network_damage m_send_network_damage;

		functions::trigger_script_event m_trigger_script_event;

		// Bitbuffer Read/Write START
		functions::read_bitbuf_dword m_read_bitbuf_dword;
		functions::read_bitbuf_string m_read_bitbuf_string;
		functions::read_bitbuf_bool m_read_bitbuf_bool;
		functions::read_bitbuf_array m_read_bitbuf_array;
		functions::write_bitbuf_qword m_write_bitbuf_qword;
		functions::write_bitbuf_dword m_write_bitbuf_dword;
		functions::write_bitbuf_int64 m_write_bitbuf_int64;
		functions::write_bitbuf_int32 m_write_bitbuf_int32;
		functions::write_bitbuf_bool m_write_bitbuf_bool;
		functions::write_bitbuf_array m_write_bitbuf_array;
		// Bitbuffer Read/Write END

		// Received Event Signatures START
		PVOID m_received_event;
		functions::send_event_ack m_send_event_ack;
		// Received Event Signatures END

		PVOID m_world_model_spawn_bypass;
		memory::handle m_blame_explode;
		memory::handle m_explosion_patch;

		functions::queue_packet m_queue_packet;
		functions::send_packet m_send_packet;

		//Sync Signatures START
		PVOID m_received_clone_sync;
		functions::get_sync_tree_for_type m_get_sync_tree_for_type;
		functions::get_sync_type_info m_get_sync_type_info;
		functions::get_net_object m_get_net_object;
		//Sync Signatures END

		functions::get_gameplay_cam_coords m_get_gameplay_cam_coords;

		functions::request_control m_request_control;

		CNetworkObjectMgr** m_network_object_mgr;

		PVOID m_receive_net_message;
		PVOID m_get_network_event_data;
		PVOID m_assign_physical_index;

		PVOID m_network_player_mgr_init;
		PVOID m_network_player_mgr_shutdown;

		PVOID m_network_can_access_multiplayer;
		PVOID m_terminate_game;

		PVOID m_update_script_threads;

		PVOID m_add_plane_lift;
		PVOID m_apply_plane_thrust;
	};

	inline pointers* g_pointers{};
}
