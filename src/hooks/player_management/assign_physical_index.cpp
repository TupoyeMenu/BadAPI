#include "gta/script/fiber_pool.hpp"
#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"

#include "lua/lua_manager.hpp"

#include <network/Network.hpp>

#include "gta/gta_util.hpp"

#include "util/header_wrappers/include_as_enhaced.hpp"
#include "gta/netPlayer.hpp"
#include "util/header_wrappers/include_as_legacy.hpp"
#include "gta/netPlayer.hpp"
#include "util/header_wrappers/clear_include.hpp"


namespace big
{
	inline bool is_spoofed_host_token(rage::rlGamerInfo* info)
	{
		if (info->m_host_token < INT_MAX)
			return true;

		return (info->m_peer_id >> 32) != (info->m_host_token >> 32);
	}

	void* hooks::assign_physical_index(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index)
	{
		const auto* net_player_data = CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, player, ->GetGamerInfo());

		if (new_index == static_cast<uint8_t>(-1))
		{
			g_player_service->player_leave(player);

			if (net_player_data)
			{
				g_lua_manager->trigger_event<"PlayerLeave">(net_player_data->m_name, (uint64_t)player);
			}

			return g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);
		}

		const auto result = g_hooking->get_original<hooks::assign_physical_index>()(netPlayerMgr, player, new_index);
		g_player_service->player_join(player);
		if (net_player_data)
		{
			g_lua_manager->trigger_event<"PlayerJoin">(net_player_data->m_name, CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, player, ->m_PlayerIndex), (uint64_t)player);
		}
		return result;
	}

}
