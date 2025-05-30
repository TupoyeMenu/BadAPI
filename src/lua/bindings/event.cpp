#include "lua/lua_module.hpp"

namespace lua::event
{
	// Lua API: Table
	// Name: menu_event
	// Table containing all possible events to which you can respond.

	// Lua API: Field
	// Table: menu_event
	// Field: PlayerLeave: integer
	// Event that is triggered when a player leave the game session.
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.PlayerLeave, function (player_name, net_player_ptr)
	//     log.info(player_name)
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: PlayerJoin: integer
	// Event that is triggered when a player join the game session.
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.PlayerJoin, function (player_name, player_id, net_player_ptr)
	//     log.info(player_name)
	//     log.info(player_id)
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: PlayerMgrInit: integer
	// Event that is triggered when the player manager initialize. Usually called when we are joining a session.
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.PlayerMgrInit, function (net_player_mgr_ptr)
	//     log.info("Player manager inited, we just joined a session.")
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: PlayerMgrShutdown: integer
	// Event that is triggered when the player manager is about to be shutdown. Usually called when we are leaving a session.
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.PlayerMgrShutdown, function (net_player_mgr_ptr)
	//     log.info("Player manager inited, we just left a session.")
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: MenuUnloaded: integer
	// Event that is triggered when we unload.. whatever this is.
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.MenuUnloaded, function ()
	//     log.info("Menu unloaded.")
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: Wndproc: integer
	// Event that is triggered when Wndproc is called
	// **Example Usage:**
	// ```lua
	// event.register_handler(menu_event.Wndproc, function (hwnd, msg, wparam, lparam)
	//     if msg == 132 then return end
	//     log.debug("hwnd = " .. tostring(hwnd) .. ", msg = " .. tostring(msg) .. ", wparam = " .. tostring(wparam) .. ", lparam = " .. tostring(lparam))
	// end)
	// ```

	// Lua API: Field
	// Table: menu_event
	// Field: Draw: integer
	// Called every frame, you can draw ImGui here.

	// Lua API: Field
	// Table: menu_event
	// Field: LuaInitFinished: integer
	// Called when lua_manager has finished constructing and all lua files have been loaded.

	// Lua API: Table
	// Name: event
	// Table for responding to various events. The list of events is available in the menu_event table.

	// Lua API: Function
	// Table: event
	// Name: register_handler
	// Param: menu_event: integer: The menu_event that we want to respond to.
	// Param: identifier: string: A unique identifier for this event, calling this function again with the same identifier will override the previous one.
	// Param: func: function: The function that will be called.
	// Register a function that will be called each time the corresponding menu_event is triggered.
	static void register_handler(const menu_event& menu_event, const std::string_view& identifier, sol::protected_function func, sol::this_state state)
	{
		big::lua_module* module = sol::state_view(state)["!this"];

		module->m_event_callbacks[menu_event][rage::joaat(identifier)] = func;
	}

	// Lua API: Function
	// Table: event
	// Name: trigger
	// Param: menu_event: integer: The menu_event that we want to trigger.
	// Param: p2: any: Argument to pass down to the event.
	// Param: p3: any: Argument to pass down to the event.
	// Trigger a menu_event. Uses variadic_args.
	static void trigger(const menu_event& menu_event, sol::variadic_args args, sol::this_state state)
	{
		big::lua_module* module = sol::state_view(state)["!this"];

		for (auto event : module->m_event_callbacks[menu_event])
		{
			event.second(args);
		}
	}

	void bind(sol::state& state)
	{
		state.new_enum<menu_event>("menu_event",
		    {
		        {"PlayerLeave", menu_event::PlayerLeave},
		        {"PlayerJoin", menu_event::PlayerJoin},
		        {"PlayerMgrInit", menu_event::PlayerMgrInit},
		        {"MenuUnloaded", menu_event::MenuUnloaded},
		        {"Wndproc", menu_event::Wndproc},
		        {"Draw", menu_event::Draw},
		        {"LuaInitFinished", menu_event::LuaInitFinished},
		    });


		auto ns                = state["event"].get_or_create<sol::table>();
		ns["register_handler"] = register_handler;
		ns["trigger"]          = trigger;
		// TODO: Check if triggering events works.
	}
}
