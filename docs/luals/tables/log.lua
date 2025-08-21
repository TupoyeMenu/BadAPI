---@meta
---@class log
---Table containing functions for printing to console / log file.
log = {}
-- Functions (6)

---Logs an informational message.
---**Example Usage:**
---```lua
---log.info(...)
---```
---@param ... any
function log.info(...) end


---Logs a warning message.
---**Example Usage:**
---```lua
---log.warning(...)
---```
---@param ... any
function log.warning(...) end


---Logs a debug message.
---**Example Usage:**
---```lua
---log.debug(...)
---```
---@param ... any
function log.debug(...) end


---Logs a fatal message.
---**Example Usage:**
---```lua
---log.fatal(...)
---```
---@param ... any
function log.fatal(...) end


---**Example Usage:**
---```lua
---table<integer, LogMessage> = log.get_log_messages()
---```
---@return table<integer, LogMessage> # An array of LogMessages
function log.get_log_messages() end


---Clear the table returned by log.get_log_messages
---**Example Usage:**
---```lua
---log.clear_log_messages()
---```
function log.clear_log_messages() end



