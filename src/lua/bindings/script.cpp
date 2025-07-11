#include "script.hpp"

#include "gta/gta_util.hpp"
#include "lua/lua_manager.hpp"
#include "memory/pattern.hpp"
#include "util/scripts.hpp"

namespace lua::script
{
	static script_util dummy_script_util;

	// Lua API: Function
	// Table: script
	// Name: yield
	// Returns: integer: 0
	int yield()
	{
		return 0;
	}
	int script_util::yield()
	{
		return 0;
	}

	// Lua API: Function
	// Table: script
	// Name: sleep
	// Param: ms: number: time to sleep for, in milliseconds
	// Returns: integer: time slept for
	int sleep(int ms)
	{
		return ms;
	}
	int script_util::sleep(int ms)
	{
		return ms;
	}

	// Lua API: Table
	// Name: script
	// Table containing helper functions related to gta scripts.

	// Lua API: Function
	// Table: script
	// Name: register_looped
	// Param: name: string: name of your new looped script
	// Param: func: function: function that will be executed in a forever loop.
	// Returns: internal_script: Script utils for this script
	// Registers a function that will be looped as a gta script.
	// **Example Usage:**
	// ```lua
	// script.register_looped("nameOfMyLoopedScript", function (script)
	//     -- sleep until next game frame
	//     script:yield()
	//
	//     local ModelHash = joaat("adder")
	//     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
	//     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
	//     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
	//         script:yield()
	//     end
	//     local myPed = PLAYER.PLAYER_PED_ID()
	//     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
	//     -- Spawns a networked vehicle on your current coords
	//     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
	//     -- removes model from game memory as we no longer need it
	//     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
	//     -- sleep for 2s
	//     script:sleep(2000)
	//     ENTITY.DELETE_ENTITY(spawnedVehicle)
	// end)
	// ```
	static std::shared_ptr<big::script> register_looped(const std::string& name, sol::protected_function func_, sol::this_state state)
	{
		big::lua_module* module = sol::state_view(state)["!this"];

		std::shared_ptr<big::script> lua_script = std::make_shared<big::script>(
		    [func_, state]() mutable {
			    sol::thread t       = sol::thread::create(state);
			    sol::coroutine func = sol::coroutine(t.state(), func_);

			    while (big::g_running)
			    {
				    auto res = func(dummy_script_util);

				    if (!res.valid())
				    {
					    break;
				    }

				    if (func.runnable())
				    {
					    big::script::get_current()->yield(std::chrono::milliseconds(res.return_count() ? res[0] : 0));
				    }
				    else
				    {
					    big::script::get_current()->yield();
				    }
			    }
		    },
		    name);

		module->m_registered_scripts[rage::joaat(name)] = lua_script;

		return lua_script;
	}

	// Lua API: Function
	// Table: script
	// Name: run_in_fiber
	// Param: func: function: function that will be executed once in the fiber pool.
	// Returns: internal_script: Script utils for this script
	// Executes a function once inside the fiber pool, you can call natives inside it and yield or sleep.
	// **Example Usage:**
	// ```lua
	// script.run_in_fiber(function (script)
	//     -- sleep until next game frame
	//     script:yield()
	//
	//     local ModelHash = joaat("adder")
	//     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
	//     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
	//     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
	//         script:yield()
	//     end
	//     local myPed = PLAYER.PLAYER_PED_ID()
	//     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
	//     -- Spawns a networked vehicle on your current coords
	//     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
	//     -- removes model from game memory as we no longer need it
	//     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
	//     -- sleep for 2s
	//     script:sleep(2000)
	//     ENTITY.DELETE_ENTITY(spawnedVehicle)
	// end)
	// ```
	static std::shared_ptr<big::script> run_in_fiber(sol::protected_function func_, sol::this_state state)
	{
		big::lua_module* module = sol::state_view(state)["!this"];

		static size_t name_i = 0;
		std::string job_name = module->module_name() + std::to_string(name_i++);

		// We make a new script for lua state destruction timing purposes, see lua_module dctor for more info.
		std::shared_ptr<big::script> lua_script = std::make_shared<big::script>(
		    [func_, state]() mutable {
			    sol::thread t       = sol::thread::create(state);
			    sol::coroutine func = sol::coroutine(t.state(), func_);

			    while (big::g_running)
			    {
				    auto res = func(dummy_script_util);

				    if (!res.valid())
				    {
					    break;
				    }

				    if (func.runnable())
				    {
					    big::script::get_current()->yield(std::chrono::milliseconds(res.return_count() ? res[0] : 0));
				    }
				    else
				    {
					    break;
				    }
			    }
		    },
		    job_name);

		module->m_registered_scripts[rage::joaat(job_name)] = lua_script;

		return lua_script;
	}

	// Lua API: function
	// Table: script
	// Name: remove
	// Param: script_name: string: The name of the script.
	// Returns: boolean: true if we removed the script
	// Removes a script added with script.register_looped
	static bool remove(const std::string& script_name, sol::this_state state)
	{
		big::lua_module* module = sol::state_view(state)["!this"];

		if (module->m_registered_scripts.contains(rage::joaat(script_name)))
		{
			module->m_registered_scripts.erase(rage::joaat(script_name));
			return true;
		}

		return false;
	}

	// Lua API: function
	// Table: script
	// Name: is_active
	// Param: script_name: string: The name of the script.
	// Returns true if the specified script is currently active/running.
	// **Example Usage:**
	// ```lua
	// local is_freemode_active = script.is_active("freemode")
	// ```
	static bool is_active(const std::string& script_name)
	{
		if (auto script = big::gta_util::find_script_thread(rage::joaat(script_name)))
			return true;

		return false;
	}

	// Lua API: function
	// Table: script
	// Name: execute_as_script
	// Param: script_name: string: Target script thread.
	// Param: func: function: Function that will be executed once in the script thread.
	static void execute_as_script(const std::string& script_name, sol::protected_function func)
	{
		big::gta_util::execute_as_script(rage::joaat(script_name), func);
	}

	void bind(sol::state& state)
	{
		auto ns                 = state["script"].get_or_create<sol::table>();
		ns["register_looped"]   = register_looped;
		ns["run_in_fiber"]      = run_in_fiber;
		ns["remove"]            = remove;
		ns["is_active"]         = is_active;
		ns["execute_as_script"] = execute_as_script;

		ns["yield"] = sol::yielding(&yield);
		ns["sleep"] = sol::yielding(&sleep);

		auto usertype = state.new_usertype<script_util>("script_util");

		usertype["yield"] = sol::yielding(&script_util::yield);
		usertype["sleep"] = sol::yielding(&script_util::sleep);

		auto internal_script             = state.new_usertype<big::script>("internal_script");
		internal_script["name"]          = &big::script::name;
		internal_script["is_enabled"]    = &big::script::is_enabled;
		internal_script["set_enabled"]   = &big::script::set_enabled;
		internal_script["is_toggleable"] = &big::script::is_toggleable;
		internal_script["is_done"]       = &big::script::is_done;
	}
}
