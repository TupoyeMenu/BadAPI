/**
 * @file hooking.cpp
 * @brief Hooking initialization.
 */

#include "hooking.hpp"

#include "gta/pointers.hpp"
#include "gta/script/invoker.hpp"
#include "gta/script/script_mgr.hpp"

#include <MinHook.h>
#include <fibersapi.h>

namespace big
{
	hooking::hooking()
	{
		// The only instances in that vector at this point should only be the "lazy" hooks
		// aka the ones that still don't have their m_target assigned
		for (auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->set_target_and_create_hook(detour_hook_helper->m_on_hooking_available());
		}

		auto swapchain_vft = *reinterpret_cast<void***>(*g_pointers->m_swapchain);
		detour_hook_helper::add<hooks::swapchain_present>("Present", swapchain_vft[hooks::swapchain_present_index]);
		detour_hook_helper::add<hooks::swapchain_resizebuffers>("ResizeBuffers", swapchain_vft[hooks::swapchain_resizebuffers_index]);

		if (!g_is_enhanced)
		{
			detour_hook_helper::add<hooks::terminate_game>("Terminate Game", (void*)g_pointers->m_terminate_game); // Inlined in enhanced
			detour_hook_helper::add<hooks::handle_join_request>("Handle Join Request", (void*)g_pointers->m_handle_join_request);
		}
		detour_hook_helper::add<hooks::receive_net_message>("Receive Net Message", (void*)g_pointers->m_receive_net_message);

		detour_hook_helper::add<hooks::prepare_metric_for_sending>("Prepare Metric For Sending", (void*)g_pointers->m_prepare_metric_for_sending);

		detour_hook_helper::add<hooks::run_script_threads>("Script hook", (void*)g_pointers->m_run_script_threads);
		detour_hook_helper::add<hooks::init_native_tables>("Init Native Tables", (void*)g_pointers->m_init_native_tables);
		detour_hook_helper::add<hooks::script_vm>("Script VM", (void*)g_pointers->m_script_vm);

		detour_hook_helper::add<hooks::network_player_mgr_init>("Network Player Mgr Init", (void*)g_pointers->m_network_player_mgr_init);
		detour_hook_helper::add<hooks::network_player_mgr_shutdown>("Network Player Mgr Shutdown", (void*)g_pointers->m_network_player_mgr_shutdown);
		detour_hook_helper::add<hooks::assign_physical_index>("Assign Physical Index", (void*)g_pointers->m_assign_physical_index);

		g_hooking = this;
	}

	hooking::~hooking()
	{
		if (m_enabled)
			disable();

		g_hooking = nullptr;
	}

	void hooking::enable()
	{
		m_og_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hooks::wndproc)));

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->enable();
		}

		MH_ApplyQueued();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_enabled = false;

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			detour_hook_helper->m_detour_hook->disable();
		}

		SetWindowLongPtrW(g_pointers->m_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_og_wndproc));

		MH_ApplyQueued();

		for (const auto& detour_hook_helper : m_detour_hook_helpers)
		{
			delete detour_hook_helper;
		}
		m_detour_hook_helpers.clear();
	}

	hooking::detour_hook_helper::~detour_hook_helper()
	{
		delete m_detour_hook;
	}

	void hooking::detour_hook_helper::enable_hook_if_hooking_is_already_running()
	{
		if (g_hooking && g_hooking->m_enabled)
		{
			if (m_on_hooking_available)
			{
				m_detour_hook->set_target_and_create_hook(m_on_hooking_available());
			}

			m_detour_hook->enable();
			MH_ApplyQueued();
		}
	}

	bool hooks::run_script_threads(std::uint32_t ops_to_execute)
	{
		g_native_invoker.cache_handlers();

		if (g_running)
		{
			g_script_mgr.tick();
		}

		return g_hooking->get_original<run_script_threads>()(ops_to_execute);
	}
}
