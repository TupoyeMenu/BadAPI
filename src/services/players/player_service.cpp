#include "player_service.hpp"

#include "gta/gta_util.hpp"
#include "util/math.hpp"


namespace big
{
	player_service::player_service() :
	    m_selected_player(m_dummy)
	{
		g_player_service = this;

		const auto network_player_mgr = gta_util::get_network_player_mgr();
		if (!network_player_mgr)
			return;

		for (uint16_t i = 0; i < network_player_mgr->m_player_limit; ++i)
			player_join(network_player_mgr->m_player_list[i]);
	}

	player_service::~player_service()
	{
		g_player_service = nullptr;
	}

	void player_service::do_cleanup()
	{
		m_players_sending_modder_beacons.clear();
		m_selected_player = m_dummy;
		m_players.clear();
	}

	player_ptr player_service::get_by_msg_id(uint32_t msg_id) const
	{
		for (const auto& [_, player] : m_players)
		{
			if (auto net_game_player = player->get_net_game_player())
			{
				if (net_game_player->m_msg_id == msg_id)
				{
					return player;
				}
			}
		}
		return nullptr;
	}

	player_ptr player_service::get_by_id(Player id) const
	{
		for (const auto& [_, player] : m_players)
		{
			if (player && player->id() == id)
			{
				return player;
			}
		}
		return nullptr;
	}

	player_ptr player_service::get_by_rid(uint64_t rid) const
	{
		for (const auto& [name, player] : m_players)
			if (player->get_net_data()->m_gamer_handle.m_rockstar_id == rid)
				return player;
		return nullptr;
	}

	player_ptr player_service::get_by_host_token(uint64_t token) const
	{
		for (const auto& player : m_players | std::ranges::views::values)
		{
			if (auto net_data = player->get_net_data())
			{
				if (net_data->m_host_token == token)
				{
					return player;
				}
			}
		}
		return nullptr;
	}

	player_ptr player_service::get_selected() const
	{
		return m_selected_player;
	}

	void player_service::player_join(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr)
			return;

		auto plyr = std::make_shared<player>(net_game_player);
		m_players.insert({plyr->get_name(), std::move(plyr)});
	}

	void player_service::player_leave(CNetGamePlayer* net_game_player)
	{
		if (net_game_player == nullptr)
			return;

		if (m_selected_player && m_selected_player->equals(net_game_player))
			m_selected_player = m_dummy;

		if (auto it = std::find_if(m_players.begin(),
		        m_players.end(),
		        [net_game_player](const auto& p) {
			        return p.second->id() == net_game_player->m_player_id;
		        });
		    it != m_players.end())
		{
			m_players.erase(it);
		}
	}

	void player_service::mark_player_as_sending_modder_beacons(std::uint64_t rid)
	{
		m_players_sending_modder_beacons.insert(rid);
	}

	bool player_service::did_player_send_modder_beacon(std::uint64_t rid)
	{
		return m_players_sending_modder_beacons.contains(rid);
	}

	void player_service::set_selected(player_ptr plyr)
	{
		m_selected_player = plyr;
	}
}
