/**
 * @file entity.hpp
 * @brief Basic entity related functions.
 */

#pragma once

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
	 * @brief Checks if you have control over net_object
	 * 
	 * @param net_object Entity to check control of.
	 * @return True if you have control over entity.
	 */
	bool network_has_control_of_entity(rage::netObject* net_object);
}
