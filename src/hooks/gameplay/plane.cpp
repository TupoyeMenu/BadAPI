#include "hooking/hooking.hpp"
#include "lua/lua_manager.hpp"

namespace big
{
	void hooks::add_plane_lift(CVehicle* _this, rage::fvector3* velocity, float p3, float p4, float p5, bool p6)
	{
		if(g_lua_manager)
		{
			auto res = g_lua_manager->trigger_event<menu_event::AddPlaneLift, bool>((uint64_t)_this, velocity, p3, p4, p5, p6, (uint64_t)g_hooking->get_original<hooks::add_plane_lift>());
			if(!res.has_value()) // Replace the function if any bool is returned.
			{
				g_hooking->get_original<hooks::add_plane_lift>()(_this, velocity, p3, p4, p5, p6);
			}
			}
		else
		{
			g_hooking->get_original<hooks::add_plane_lift>()(_this, velocity, p3, p4, p5, p6);
		}
	}

	void hooks::apply_plane_thrust(CVehicle* _this, float p2,float p3,float p4,float p5,float p6,bool p7)
	{
		if(g_lua_manager)
		{
			auto res = g_lua_manager->trigger_event<menu_event::ApplyPlaneThrust, bool>((uint64_t)_this, p2, p3, p4, p5, p6, p7, (uint64_t)g_hooking->get_original<hooks::apply_plane_thrust>());
			if(!res.has_value()) // Replace the function if any bool is returned.
			{
				g_hooking->get_original<hooks::apply_plane_thrust>()(_this, p2, p3, p4, p5, p6, p7);
			}
		}
		else
		{
			g_hooking->get_original<hooks::apply_plane_thrust>()(_this, p2, p3, p4, p5, p6, p7);
		}
	}
}
