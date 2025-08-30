#include "hooking/hooking.hpp"
#include "native_hooks/native_hooks.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	bool hooks::init_native_tables(rage::scrProgram* program)
	{
		bool ret = g_hooking->get_original<hooks::init_native_tables>()(program);

		// Don't hook empty threads from cache_handlers to avoid co-loading issues.
		if(program->m_code_blocks && program->m_code_size)
		{
			g_script_patcher_service->on_script_load(program);
			g_native_hooks->hook_program(program);

			g_lua_manager->trigger_event<"InitNativeTables">((uint64_t)program);
		}

		return ret;
	}
}
