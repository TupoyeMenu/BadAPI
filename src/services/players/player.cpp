#include "player.hpp"

#include "gta/gta_util.hpp"
#include "network/CNetGamePlayer.hpp"

#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

namespace big
{
	player::player(CNetGamePlayer* net_game_player) :
	    m_net_game_player(net_game_player)
	{
	}

	CVehicle* player::get_current_vehicle() const
	{
		if (const auto ped = get_ped(); ped != nullptr)
			if (const auto vehicle = ped->m_vehicle; vehicle != nullptr)
				return vehicle;
		return nullptr;
	}

	const char* player::get_name() const
	{
		return get_net_game_player() == nullptr ? "" : m_net_game_player->get_name();
	}

	rage::rlGamerInfo* player::get_net_data() const
	{
		return get_net_game_player() == nullptr ? nullptr : m_net_game_player->get_net_data();
	}

	CNetGamePlayer* player::get_net_game_player() const
	{
		return (m_net_game_player == nullptr || m_net_game_player->m_player_info == nullptr) ? nullptr : m_net_game_player;
	}

	int64_t player::get_rockstar_id() const
	{
		if (auto net_data = get_net_data())
			return net_data->m_gamer_handle.m_rockstar_id;
		return 0;
	}

	CPed* player::get_ped() const
	{
		if (auto player_info = get_player_info())
			if (auto ped = player_info->m_ped)
				return ped;
		return nullptr;
	}

	CPlayerInfo* player::get_player_info() const
	{
		if (auto net_player = get_net_game_player())
			return net_player->m_player_info;
		return nullptr;
	}


	uint8_t player::id() const
	{
		if (gta_util::get_network_player_mgr()->m_player_count > 0)
			return get_net_game_player() == nullptr ? -1 : m_net_game_player->m_player_id;
		else
			return self::id;
	}

	bool player::is_host() const
	{
		return get_net_game_player() == nullptr ? false : m_net_game_player->is_host();
	}

	bool player::is_valid() const
	{
		return get_net_game_player() == nullptr ? false : m_net_game_player->is_valid();
	}

	bool player::equals(const CNetGamePlayer* net_game_player) const
	{
		return net_game_player == get_net_game_player();
	}

	std::string player::to_lowercase_identifier() const
	{
		std::string lower = get_name();
		std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

		return lower;
	}
}
