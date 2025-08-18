#include "entity.hpp"

#include "gta/net_object_mgr.hpp"
#include "gta/script/script.hpp"

#include <entities/CDynamicEntity.hpp>


namespace big::entity
{
	bool network_has_control_of_entity(rage::netObject* net_object)
	{
		return !net_object || !net_object->m_is_remote && (net_object->m_wants_to_be_owner == -1);
	}

	bool take_control_of(Entity ent, int timeout)
	{
		if (!*g_pointers->m_is_session_started)
			return true;

		auto hnd = g_pointers->m_handle_to_ptr(ent);

		if (!hnd || !hnd->m_net_object)
			return false;

		if (hnd->m_entity_type != 3 && hnd->m_entity_type != 4 && hnd->m_entity_type != 5)
			return false;

		for (int i = 0; i <= timeout; ++i)
		{
			if (network_has_control_of_entity(hnd->m_net_object))
				return true;

			g_pointers->m_request_control(hnd->m_net_object);

			if (timeout != 0)
				script::get_current()->yield();
		}

		return false;
	}
}
