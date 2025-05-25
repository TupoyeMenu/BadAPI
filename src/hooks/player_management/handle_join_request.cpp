#include "hooking/hooking.hpp"
#include "gta/pointers.hpp"

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
	 * @param is_transition_session Is not actually a bool, seems to be some sort of class.
	 * @return bool 
	 */
	bool hooks::handle_join_request(Network* network, rage::snSession* session, rage::rlGamerInfo* player_info, CJoinRequestContext* ctx, BOOL is_transition_session)
	{
		auto rockstar_id = player_info->m_gamer_handle.m_rockstar_id;
		auto player_name = player_info->m_name;

		LOG(VERBOSE) << player_info->m_name << " " << is_transition_session;

		auto send_response = [ctx](int block_join_reason = 1) {
			CMsgJoinResponse response{};
			response.m_status_code = block_join_reason;
			g_pointers->m_write_join_response_data(&response, ctx->m_join_response_data, 512, &ctx->m_join_response_size);
		};

		send_response(0);
		LOGF(INFO, "Allowed {} to join", player_name);
		return true;
	}
}
