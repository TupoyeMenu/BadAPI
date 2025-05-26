/**
 * @file entity.hpp
 * @brief Basic entity related functions.
 */

#pragma once
#include "services/players/player.hpp"

#include <rage/vector.hpp>
#include <script/types.hpp>

namespace rage
{
	class netObject;
	class CEntity;
}

namespace big::entity
{
	/**
	 * @brief Attemts to take control of given entity
	 * 
	 * @param ent Entity to take control of.
	 * @param timeout When to give up trying to take control. In for loop iterations. 
	 * @return True if the control has been taken.
	 */
	bool take_control_of(Entity ent, int timeout = 300);

	/**
	 * @brief Raycasts for entitys from the current camera forward.
	 * 
	 * @param ent Entity that we have hit.
	 * @return True if hit something other then the sky.
	 */
	bool raycast(Entity* ent);
	bool raycast(Vector3* endcoor);

	/**
	 * @brief Checks if you have control over net_object
	 * 
	 * @param net_object Entity to check control of.
	 * @return True if you have control over entity.
	 */
	bool network_has_control_of_entity(rage::netObject* net_object);

	bool load_ground_at_3dcoord(Vector3& location);
	bool request_model(rage::joaat_t hash);
	double distance_to_middle_of_screen(const rage::fvector2& screen_pos);
	void force_remove_network_entity(rage::CDynamicEntity* entity, player_ptr for_player = nullptr, bool delete_locally = true);
	void force_remove_network_entity(std::uint16_t net_id, int ownership_token = -1, player_ptr for_player = nullptr, bool delete_locally = true);
}
