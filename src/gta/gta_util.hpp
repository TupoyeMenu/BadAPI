#pragma once

// clang-format off
#include "util/header_wrappers/include_as_enhaced.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "util/header_wrappers/include_as_legacy.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "util/header_wrappers/clear_include.hpp"
// clang-format on

#include "gta/script/big_program.hpp"
#include "pointers.hpp"

#include <network/CNetworkPlayerMgr.hpp>
#include <ped/CPedFactory.hpp>
#include <script/scrProgramTable.hpp>


#define CROSS_CLASS_ACCESS(legacy_type, enhanced_type, variable, expression) \
	(g_is_enhanced ? ((enhanced_type*)variable)expression : ((legacy_type*)variable)expression)

namespace big::gta_util
{
	inline CPed* get_local_ped()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			return ped_factory->m_local_ped;
		}

		return nullptr;
	}

	inline CVehicle* get_local_vehicle()
	{
		if (const auto ped = get_local_ped(); ped)
		{
			if (const auto veh = ped->m_vehicle; veh)
			{
				return veh;
			}
		}
		return nullptr;
	}


	inline CPlayerInfo* get_local_playerinfo()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_player_info;
			}
		}

		return nullptr;
	}

	inline CNetworkPlayerMgr* get_network_player_mgr()
	{
		return *g_pointers->m_network_player_mgr;
	}

	inline Network* get_network()
	{
		return *g_pointers->m_network;
	}

	template<typename F, typename... Args>
	void execute_as_script(void* thread, F&& callback, Args&&... args)
	{
		if (!thread)
			return;

		auto tls_ctx = legacy::rage::tlsContext::get();
		auto og_thread = CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread);

		CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = thread;
		CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = true;

		std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

		CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = og_thread;
		CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = og_thread != nullptr;
	}

	template<typename F, typename... Args>
	void execute_as_script(rage::joaat_t script_hash, F&& callback, Args&&... args)
	{
		auto tls_ctx = legacy::rage::tlsContext::get();
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (!thread || CROSS_CLASS_ACCESS(legacy::rage::scrThread, enhanced::rage::scrThread, thread, ->m_context.m_thread_id) == 0
			    || CROSS_CLASS_ACCESS(legacy::rage::scrThread, enhanced::rage::scrThread, thread, ->m_context.m_script_hash) != script_hash)
				continue;

			auto og_thread = CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread);

			CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = thread;
			CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = true;

			std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

			CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = og_thread;
			CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = og_thread != nullptr;

			return;
		}
	}


	inline rage::scrThread* find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread && CROSS_CLASS_ACCESS(legacy::rage::scrThread, enhanced::rage::scrThread, thread, ->m_context.m_thread_id)
			    && CROSS_CLASS_ACCESS(legacy::rage::scrThread, enhanced::rage::scrThread, thread, ->m_context.m_script_hash) == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}

	inline rage::scrThread* find_script_thread_by_id(std::uint32_t id)
	{
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (thread && CROSS_CLASS_ACCESS(legacy::rage::scrThread, enhanced::rage::scrThread, thread, ->m_context.m_thread_id) == id)
			{
				return thread;
			}
		}

		return nullptr;
	}

	inline rage::scrProgram* find_script_program(rage::joaat_t hash)
	{
		for (auto& script : *g_pointers->m_script_program_table)
		{
			if (script.m_program && script.m_program->m_name_hash == hash)
				return script.m_program;
		}

		return nullptr;
	}
}
