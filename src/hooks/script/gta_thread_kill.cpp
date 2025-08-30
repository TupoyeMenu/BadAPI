#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	rage::eThreadState hooks::gta_thread_kill(GtaThread* thread)
	{
		const auto result = g_hooking->get_original<gta_thread_kill>()(thread);

		g_lua_manager->trigger_event<"GTAThreadKill">((uint64_t)thread);

		return result;
	}
}
