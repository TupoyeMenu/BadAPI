#include "hooking/hooking.hpp"

#include "lua/lua_manager.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	bool hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		bool result = g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		if (g_lua_manager) [[likely]]
		{
			g_lua_manager->trigger_event<"PlayerMgrInit">((uint64_t)_this);
		}

		return result;
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		if (g_lua_manager) [[likely]]
		{
			g_lua_manager->trigger_event<"PlayerMgrShutdown">((uint64_t)_this);
		}
	}
}
