#include "player.hpp"

#include "common.hpp"
#include "gta/gta_util.hpp"

#include "util/header_wrappers/include_as_enhaced.hpp"
#include "gta/netPlayer.hpp"
#include "util/header_wrappers/include_as_legacy.hpp"
#include "gta/netPlayer.hpp"
#include "util/header_wrappers/clear_include.hpp"

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
		return get_net_game_player() == nullptr ? "" : CROSS_CLASS_ACCESS(legacy::rage::netPlayer, enhanced::rage::netPlayer, m_net_game_player, ->GetName());
	}

	rage::rlGamerInfo* player::get_net_data() const
	{
		return get_net_game_player() == nullptr ? nullptr : CROSS_CLASS_ACCESS(legacy::rage::netPlayer, enhanced::rage::netPlayer, m_net_game_player, ->GetGamerInfo());
	}

	CNetGamePlayer* player::get_net_game_player() const
	{
		return (m_net_game_player == nullptr || CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, m_net_game_player, ->m_PlayerInfo) == nullptr) ? nullptr : m_net_game_player;
	}

	int64_t player::get_rockstar_id() const
	{
		if (auto net_data = get_net_data())
			return net_data->m_gamer_handle.m_rockstar_id;
		return 0;
	}

	CPed* player::get_ped() const
	{
		if (g_is_enhanced)
			return nullptr;

		if (auto player_info = get_player_info())
			if (auto ped = player_info->m_ped)
				return ped;
		return nullptr;
	}

	CPlayerInfo* player::get_player_info() const
	{
		if (auto net_player = get_net_game_player())
			return CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, m_net_game_player, ->m_PlayerInfo);
		return nullptr;
	}


	uint8_t player::id() const
	{
		if (gta_util::get_network_player_mgr()->m_player_count > 0)
			return get_net_game_player() == nullptr ? -1 : CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, m_net_game_player, ->m_PlayerIndex);
		else
			return self::id;
	}

	bool player::is_host() const
	{
		return get_net_game_player() == nullptr ? false : CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, m_net_game_player, ->IsHost());
	}

	bool player::is_valid() const
	{
		return get_net_game_player() == nullptr ? false : CROSS_CLASS_ACCESS(legacy::CNetGamePlayer, enhanced::CNetGamePlayer, m_net_game_player, ->IsPhysical());
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
