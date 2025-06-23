---@meta
---Class for gta script utils, the instance is usually given to you.
---@class internal_script
internal_script = {}
-- Functions (5)

---**Example Usage:**
---```lua
---string = internal_script:name()
---```
---@return string Name of this script
function internal_script:name() end


---**Example Usage:**
---```lua
---boolean = internal_script:is_enabled()
---```
---@return boolean Will this script be executed
function internal_script:is_enabled() end


---**Example Usage:**
---```lua
---internal_script:set_enabled()
---```
function internal_script:set_enabled() end


---**Example Usage:**
---```lua
---boolean = internal_script:is_toggleable()
---```
---@return boolean Can `set_enabled` be used
function internal_script:is_toggleable() end


---**Example Usage:**
---```lua
---boolean = internal_script:is_done()
---```
---@return boolean Has this script finished executing
function internal_script:is_done() end



