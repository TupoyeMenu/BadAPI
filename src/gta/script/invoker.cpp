/**
 * @file invoker.cpp
 */

#include "invoker.hpp"

#include "crossmap.hpp"
#include "gta/script/big_program.hpp"
#include "hooking/hooking.hpp"
#include "gta/pointers.hpp"
#include "script/scrNativeHandler.hpp"
#include "script/scrProgram.hpp"
#include "gta/gta_util.hpp"

namespace big
{
	native_call_context::native_call_context()
	{
		m_return_value = &m_return_stack[0];
		m_args         = &m_arg_stack[0];
	}

	void native_invoker::cache_handlers()
	{
		if (m_handlers_cached) [[likely]]
			return;

		size_t i = 0;
		for (const rage::scrNativePair& mapping : g_crossmap)
		{
			m_handler_cache[i] = (rage::scrNativeHandler)mapping.second;
			++i;
		}
		g_main_program->m_native_count = m_handler_cache.size();
		g_main_program->m_native_entrypoints = m_handler_cache.data();
		g_hooking->get_original<hooks::init_native_tables>()(g_main_program);

		m_handlers_cached = true;
	}

	rage::scrNativeHandler native_invoker::get_native_handler(rage::scrNativeHash hash)
	{
		cache_handlers();

		size_t i = 0;
		for (const rage::scrNativePair& mapping : g_crossmap)
		{
			if(mapping.second == hash) break;
			++i;
		}

		return m_handler_cache[i];
	}

	void fix_vectors(native_call_context& call_context)
	{
		for (; call_context.m_data_count;
		    call_context.m_orig[call_context.m_data_count][2].Float = call_context.m_buffer[call_context.m_data_count].z)
		{
			--call_context.m_data_count;
			call_context.m_orig[call_context.m_data_count]->Float   = call_context.m_buffer[call_context.m_data_count].x;
			call_context.m_orig[call_context.m_data_count][1].Float = call_context.m_buffer[call_context.m_data_count].y;
		}
		--call_context.m_data_count;
	}

	void native_invoker::begin_call()
	{
		m_call_context.reset();
	}

	void native_invoker::end_call(rage::scrNativeHash hash)
	{
		size_t i = 0;
		for (const rage::scrNativePair& mapping : g_crossmap)
		{
			if(mapping.first == hash) break;
			++i;
		}

		try
		{
			rage::scrNativeHandler handler = m_handler_cache.at(i);

			auto tls_ctx = legacy::rage::tlsContext::get();
			auto og_thread = CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread);
			bool og_thread_running = CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active);
			if (!og_thread)
			{
				CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = g_main_script_thread;
				CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = true;
			}

			// return address checks are no longer a thing
			handler(&m_call_context);
			fix_vectors(m_call_context);

			if (!og_thread)
			{
				CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_script_thread) = og_thread;
				CROSS_CLASS_ACCESS(legacy::rage::tlsContext, enhanced::rage::tlsContext, tls_ctx, ->m_is_script_thread_active) = og_thread_running;
			}
		}
		catch(const std::out_of_range& ex)
		{
			LOG(WARNING) << "Failed to find " << HEX_TO_UPPER(hash) << " native's handler.";
		}
	}
}