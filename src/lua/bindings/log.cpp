
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
	// Param: data: string
	// Logs an informational message.
	static void info(const std::string& data, sol::this_state state)
	{
		LOG(INFO) << data;
	}

	// Lua API: Function
	// Table: log
	// Name: warning
	// Param: data: string
	// Logs a warning message.
	static void warning(const std::string& data, sol::this_state state)
	{
		LOG(WARNING) << data;
	}

	// Lua API: Function
	// Table: log
	// Name: debug
	// Param: data: string
	// Logs a debug message.
	static void debug(const std::string& data, sol::this_state state)
	{
		LOG(VERBOSE) << data;
	}

	// Lua API: Function
	// Table: log
	// Name: fatal
	// Param: data: string
	// Logs a fatal message.
	static void fatal(const std::string& data, sol::this_state state)
	{
		LOG(FATAL) << data;
	}

	// Lua API: Function
	// Table: log
	// Name: get_log_messages
	// Returns a table of LogMessages
	static std::vector<LogMessagePtr>& get_log_messages()
	{
		return big::g_log.get_log_messages();
	}

	void bind(sol::state& state)
	{
		auto ns                = state["log"].get_or_create<sol::table>();
		ns["info"]             = info;
		ns["warning"]          = warning;
		ns["debug"]            = debug;
		ns["fatal"]            = fatal;
		ns["get_log_messages"] = get_log_messages;

		state.new_enum("eLogLevel", "VERBOSE", eLogLevel::VERBOSE, "INFO", eLogLevel::INFO, "WARNING", eLogLevel::WARNING, "FATAL", eLogLevel::FATAL);

		auto message_type       = state.new_usertype<LogMessage>("LogMessage", sol::no_constructor);
		message_type["Level"]   = &LogMessage::Level;
		message_type["Message"] = &LogMessage::Message;
	}
}
