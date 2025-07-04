---@meta
---@class script
---Table containing helper functions related to gta scripts.
script = {}
-- Functions (7)

---**Example Usage:**
---```lua
---integer = script.yield()
---```
---@return integer 0
function script.yield() end


---**Example Usage:**
---```lua
---integer = script.sleep(ms)
---```
---@param ms number time to sleep for, in milliseconds
---@return integer time slept for
function script.sleep(ms) end


---Registers a function that will be looped as a gta script.
---**Example Usage:**
---```lua
---script.register_looped("nameOfMyLoopedScript", function (script)
---     -- sleep until next game frame
---     script:yield()
---
---     local ModelHash = joaat("adder")
---     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
---     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
---     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
---         script:yield()
---     end
---     local myPed = PLAYER.PLAYER_PED_ID()
---     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
---     -- Spawns a networked vehicle on your current coords
---     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
---     -- removes model from game memory as we no longer need it
---     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
---     -- sleep for 2s
---     script:sleep(2000)
---     ENTITY.DELETE_ENTITY(spawnedVehicle)
---end)
---```
---**Example Usage:**
---```lua
---internal_script = script.register_looped(name, func)
---```
---@param name string name of your new looped script
---@param func function function that will be executed in a forever loop.
---@return internal_script Script utils for this script
function script.register_looped(name, func) end


---Executes a function once inside the fiber pool, you can call natives inside it and yield or sleep.
---**Example Usage:**
---```lua
---script.run_in_fiber(function (script)
---     -- sleep until next game frame
---     script:yield()
---
---     local ModelHash = joaat("adder")
---     if not STREAMING.IS_MODEL_IN_CDIMAGE(ModelHash) then return end
---     STREAMING.REQUEST_MODEL(ModelHash) -- Request the model
---     while not STREAMING.HAS_MODEL_LOADED(ModelHash) do -- Waits for the model to load
---         script:yield()
---     end
---     local myPed = PLAYER.PLAYER_PED_ID()
---     local myCoords = ENTITY.GET_ENTITY_COORDS(myPed, true)
---     -- Spawns a networked vehicle on your current coords
---     local spawnedVehicle = VEHICLE.CREATE_VEHICLE(ModelHash, myCoords.x, myCoords.y, myCoords.z, ENTITY.GET_ENTITY_HEADING(myPed), true, false)
---     -- removes model from game memory as we no longer need it
---     STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(ModelHash)
---     -- sleep for 2s
---     script:sleep(2000)
---     ENTITY.DELETE_ENTITY(spawnedVehicle)
---end)
---```
---**Example Usage:**
---```lua
---internal_script = script.run_in_fiber(func)
---```
---@param func function function that will be executed once in the fiber pool.
---@return internal_script Script utils for this script
function script.run_in_fiber(func) end


---Removes a script added with script.register_looped
---**Example Usage:**
---```lua
---boolean = script.remove(script_name)
---```
---@param script_name string The name of the script.
---@return boolean true if we removed the script
function script.remove(script_name) end


---Returns true if the specified script is currently active/running.
---**Example Usage:**
---```lua
---local is_freemode_active = script.is_active("freemode")
---```
---**Example Usage:**
---```lua
---script.is_active(script_name)
---```
---@param script_name string The name of the script.
function script.is_active(script_name) end


---**Example Usage:**
---```lua
---script.execute_as_script(script_name, func)
---```
---@param script_name string Target script thread.
---@param func function Function that will be executed once in the script thread.
function script.execute_as_script(script_name, func) end



