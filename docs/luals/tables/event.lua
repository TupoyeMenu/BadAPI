---@meta
---@class event
---Table for responding to various events. The list of events is available in the menu_event table.
event = {}
-- Functions (3)

---Register a function that will be called each time the corresponding menu_event is triggered.
---**Example Usage:**
---```lua
---event.register_handler(menu_event, identifier, func)
---```
---@param menu_event string The menu_event that we want to respond to.
---@param identifier string A unique identifier for this event, calling this function again with the same identifier will override the previous one.
---@param func function The function that will be called.
function event.register_handler(menu_event, identifier, func) end


---Removes the handler registered with register_handler.
---**Example Usage:**
---```lua
---boolean = event.remove(menu_event, identifier)
---```
---@param menu_event string The menu_event.
---@param identifier string A unique identifier for the event you want to remove.
---@return boolean # true if we removed the handler.
function event.remove(menu_event, identifier) end


---Trigger a menu_event. Uses variadic_args.
---**Example Usage:**
---```lua
---event.trigger(menu_event, ...)
---```
---@param menu_event string The menu_event that we want to trigger.
---@param ... any Argument to pass down to the event.
function event.trigger(menu_event, ...) end



