---@meta
---@class log
---Table containing functions for printing to console / log file.
log = {}
-- Functions (6)

---Logs an informational message.
---**Example Usage:**
---```lua
---log.info(data)
---```
---@param data string
function log.info(data) end


---Logs a warning message.
---**Example Usage:**
---```lua
---log.warning(data)
---```
---@param data string
function log.warning(data) end


---Logs a debug message.
---**Example Usage:**
---```lua
---log.debug(data)
---```
---@param data string
function log.debug(data) end


---Logs a fatal message.
---**Example Usage:**
---```lua
---log.fatal(data)
---```
---@param data string
function log.fatal(data) end


---**Example Usage:**
---```lua
---table<integer, LogMessage> = log.get_log_messages()
---```
---@return table<integer, LogMessage> An array of LogMessages
function log.get_log_messages() end


---Clear the table returned by log.get_log_messages
---**Example Usage:**
---```lua
---log.clear_log_messages()
---```
function log.clear_log_messages() end



