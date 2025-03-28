#include "core/data/menu_event.hpp"
#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"

#include "lua/lua_manager.hpp"
#include "lua/bindings/memory.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	bool hooks::network_player_mgr_init(CNetworkPlayerMgr* _this, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		bool result = g_hooking->get_original<hooks::network_player_mgr_init>()(_this, a2, a3, a4);

		g_player_service->player_join(_this->m_local_net_player);

		g_lua_manager->trigger_event<menu_event::PlayerMgrInit>(lua::memory::pointer((uint64_t)_this));

		return result;
	}

	void hooks::network_player_mgr_shutdown(CNetworkPlayerMgr* _this)
	{
		g_player_service->do_cleanup();

		g_lua_manager->trigger_event<menu_event::PlayerMgrShutdown>(lua::memory::pointer((uint64_t)_this));

		g_hooking->get_original<hooks::network_player_mgr_shutdown>()(_this);
	}
}
