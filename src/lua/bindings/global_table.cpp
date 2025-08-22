#include "gta/joaat.hpp"
#include "lua/lua_manager.hpp"
#include "lua/sol_include.hpp"
#include "util/filesystem.hpp"

namespace lua::global_table
{
	// Lua API: Table
	// Name: Global Table
	// Custom fields, functions, etc added to The Lua [Global Table](https://www.lua.org/pil/15.4.html).

	// Lua API: Function
	// Table: Global Table
	// Name: joaat
	// Param: str: string: The string that needs to be joaat hashed.
	// Returns: integer: The joaat hashed input string.

	// Lua API: Function
	// Table: Global Table
	// Name: literal_joaat
	// A case sensitive version of `joaat`.
	// Param: str: string: The case sensitive string that needs to be joaat hashed.
	// Returns: integer: The joaat hashed input string.

	static void include(const std::string& filename)
	{
		const auto scripts_path = big::filesystem::make_absolute(big::g_lua_manager->get_scripts_folder().get_path(), filename);
		if (!scripts_path)
		{
			LOG(WARNING) << "dofile is restricted to the scripts folder, and the filename provided (" << filename << ") is outside of it.";
		}
		else
		{
			big::g_lua_manager->get_module().lock()->load_and_call_script(scripts_path.value());
		}
	};

	// Lua API: Function
	// Table: Global Table
	// Name: info
	// Param: ...: any
	// Logs an informational message. Same as `log.info`.
	static void print(sol::variadic_args va, sol::this_state state)
	{
		sol::function tostring = sol::state_view(state)["tostring"];
		auto stream = LOG(INFO);
		int i = 0;
		for (auto v : va)
		{
			if (i == 0)
				stream << tostring(v).get<const std::string&>();
			else
				stream << "	" << tostring(v).get<const std::string&>();
			i++;
		}
	}

	void bind(sol::state& state)
	{
		state["joaat"]         = rage::joaat;
		state["literal_joaat"] = rage::literal_joaat;
		state["include"]       = include;
		state["dofile"]        = include;
		state["print"]         = print;
	}
}
