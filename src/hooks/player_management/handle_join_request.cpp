#include "hooking/hooking.hpp"
#include "gta/pointers.hpp"
#include "lua/lua_manager.hpp"

#include <network/CJoinRequestContext.hpp>
#include <network/CMsgJoinResponse.hpp>
#include <network/snSession.hpp>

namespace big
{
	/**
	 * @brief Checks if it's ok to let the player into the session.
	 * @param network Network.
	 * @param session Session that the player is trying to join.
	 * @param player_info Player that is joining.
	 * @param ctx Join context, just read the class.
	 * @param is_transition_session
	 * @return bool 
	 */
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session)
	{
		if (g_lua_manager) [[likely]]
		{
			auto event_ret = g_lua_manager->trigger_event<"HandleJoinRequest", bool>((uint64_t)network, (uint64_t)session, (uint64_t)player_info, (uint64_t)ctx, (int)is_transition_session);
			if (event_ret.has_value())
			{
				return event_ret.value();
			}
		}

		return g_hooking->get_original<hooks::handle_join_request>()(network, session, player_info, ctx, is_transition_session);
	}
}
