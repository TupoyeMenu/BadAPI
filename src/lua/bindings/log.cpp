
#include "logger/logger.hpp"
#include "lua/sol_include.hpp"
namespace lua::log
{
	// Lua API: Table
	// Name: log
	// Table containing functions for printing to console / log file.

	// Lua API: Function
	// Table: log
	// Name: info
	// Param: ...: any
	// Logs an informational message.
	static void info(sol::variadic_args va, sol::this_state state)
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

	// Lua API: Function
	// Table: log
	// Name: warning
	// Param: ...: any
	// Logs a warning message.
	static void warning(sol::variadic_args va, sol::this_state state)
	{
		sol::function tostring = sol::state_view(state)["tostring"];
		auto stream = LOG(WARNING);
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

	// Lua API: Function
	// Table: log
	// Name: debug
	// Param: ...: any
	// Logs a debug message.
	static void debug(sol::variadic_args va, sol::this_state state)
	{
		sol::function tostring = sol::state_view(state)["tostring"];
		auto stream = LOG(VERBOSE);
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

	// Lua API: Function
	// Table: log
	// Name: fatal
	// Param: ...: any
	// Logs a fatal message.
	static void fatal(sol::variadic_args va, sol::this_state state)
	{
		sol::function tostring = sol::state_view(state)["tostring"];
		auto stream = LOG(FATAL);
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

	// Lua API: Function
	// Table: log
	// Name: get_log_messages
	// Returns: table<integer, LogMessage>: An array of LogMessages
	static const std::vector<LogMessagePtr>& get_log_messages()
	{
		return big::g_log.get_log_messages();
	}

	// Lua API: Function
	// Table: log
	// Name: clear_log_messages
	// Clear the table returned by log.get_log_messages
	static void clear_log_messages()
	{
		big::g_log.clear_log_messages();
	}

	// Lua API: Class
	// Name: LogMessage
	// Class representing a LogMessage object.

	// Lua API: Function
	// Class: LogMessage
	// Name: Level
	// Returns: integer
	// Gets the log level of the message.

	// Lua API: Function
	// Class: LogMessage
	// Name: Message
	// Returns: string
	// Gets the string contents of the message.

	void bind(sol::state& state)
	{
		auto ns                  = state["log"].get_or_create<sol::table>();
		ns["info"]               = info;
		ns["warning"]            = warning;
		ns["debug"]              = debug;
		ns["fatal"]              = fatal;
		ns["get_log_messages"]   = get_log_messages;
		ns["clear_log_messages"] = clear_log_messages;

		state.new_enum("eLogLevel", "VERBOSE", eLogLevel::VERBOSE, "INFO", eLogLevel::INFO, "WARNING", eLogLevel::WARNING, "FATAL", eLogLevel::FATAL);

		auto message_type       = state.new_usertype<LogMessage>("LogMessage", sol::no_constructor);
		message_type["Level"]   = &LogMessage::Level;
		message_type["Message"] = &LogMessage::Message;
	}
}
