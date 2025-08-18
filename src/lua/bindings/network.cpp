#include "network.hpp"

#include "gta/pointers.hpp"
#include "gta/script/natives.hpp"

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

		SCRIPT::_SEND_TU_SCRIPT_EVENT_NEW(1, (Any*)actual_args.data(), actual_args.size(), bitset, args[0]);
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

	void bind(sol::state& state)
	{
		auto ns = state["network"].get_or_create<sol::table>();

		ns["trigger_script_event"]                     = trigger_script_event;
		ns["is_session_started"]                       = is_session_started;
		ns["give_pickup_rewards"]                      = give_pickup_rewards;
	}
}
