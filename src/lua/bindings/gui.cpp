#include "gui/gui.hpp"

#include "lua/sol_include.hpp"

#include <imgui_internal.h>

namespace lua::gui
{

	// Lua API: Function
	// Table: gui
	// Name: is_open
	// Returns: bool: Returns true if the GUI is open.
	static bool is_open()
	{
		return big::g_gui->is_open();
	}

	// Lua API: Function
	// Table: gui
	// Name: toggle
	// Param: toggle: boolean
	// Opens and closes the gui.
	static void toggle(bool toggle)
	{
		big::g_gui->toggle(toggle);
	}


	// Lua API: Function
	// Table: gui
	// Name: mouse_override
	// Returns: bool: Returns true if the mouse is overridden.
	static bool mouse_override()
	{
		return big::g_gui->mouse_override();
	}

	// Lua API: Function
	// Table: gui
	// Name: override_mouse
	// Param: override: boolean
	static void override_mouse(bool override)
	{
		big::g_gui->override_mouse(override);
	}


	void bind(sol::state& state)
	{
		auto ns                     = state["gui"].get_or_create<sol::table>();
		ns["is_open"]               = is_open;
		ns["toggle"]                = toggle;
		ns["mouse_override"]        = mouse_override;
		ns["override_mouse"]        = override_mouse;
	}
}
