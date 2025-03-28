#include "network.hpp"

#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace lua::network
{
	// Lua API: Table
	// Name: network
	// Table containing helper functions for network related features.

	// Lua API: Function
	// Table: network
	// Name: trigger_script_event
	// Param: bitset: integer
	// Param: _args: table
	// Call trigger_script_event (TSE)
	static void trigger_script_event(int bitset, sol::table _args)
	{
		auto args = convert_sequence<int32_t>(_args);

		if (args.size() >= 1)
			args[1] = big::self::id;

		std::vector<std::int64_t> actual_args;

		for (auto arg : args)
			actual_args.push_back((uint32_t)arg);

		big::g_pointers->m_trigger_script_event(1, actual_args.data(), actual_args.size(), bitset, args[0]);
	}

	// Lua API: Function
	// Table: network
	// Name: is_session_started
	// Returns true if the local player is in a multiplayer session.
	static bool is_session_started()
	{
		return *big::g_pointers->m_is_session_started;
	}

	// Lua API: Function
	// Table: network
	// Name: give_pickup_rewards
	// Param: player: integer: Index of the player.
	// Param: reward: integer: Index of the reward pickup.
	// Give the given pickup reward to the given player.
	static void give_pickup_rewards(int player, int reward)
	{
		big::g_pointers->m_give_pickup_rewards(1 << player, reward);
	}

	// Lua API: Function
	// Table: network
	// Name: get_selected_player
	// Returns: integer: Returns the index of the currently selected player in the GUI.
	static int get_selected_player()
	{
		if (big::g_player_service->get_selected()->is_valid())
			return big::g_player_service->get_selected()->id();

		return -1;
	}

	// Lua API: Function
	// Table: network
	// Name: is_player_flagged_as_modder
	// Param: player_idx: integer: Index of the player.
	// Returns: boolean: Returns true if the given player is flagged as a modder.
	static bool is_player_flagged_as_modder(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			return player->is_modder;

		return false;
	}

	void bind(sol::state& state)
	{
		auto ns = state["network"].get_or_create<sol::table>();

		ns["trigger_script_event"]                     = trigger_script_event;
		ns["is_session_started"]                       = is_session_started;
		ns["give_pickup_rewards"]                      = give_pickup_rewards;
		ns["get_selected_player"]                      = get_selected_player;
		ns["is_player_flagged_as_modder"]              = is_player_flagged_as_modder;
	}
}
