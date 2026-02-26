#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	uint32_t hooks::gta_thread_create(uint64_t p1, uint64_t p2, uint32_t p3, int p4)
	{
		const uint32_t thread_id = g_hooking->get_original<gta_thread_create>()(p1, p2, p3, p4);

		if (g_lua_manager) [[likely]]
		{
			g_lua_manager->trigger_event<"GTAThreadCreate">(thread_id);
		}

		return thread_id;
	}
}
