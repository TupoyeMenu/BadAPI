---@meta
---@class network
---Table containing helper functions for network related features.
network = {}
-- Functions (3)

---Call trigger_script_event (TSE)
---**Example Usage:**
---```lua
---network.trigger_script_event(bitset, _args)
---```
---@param bitset integer
---@param _args table
function network.trigger_script_event(bitset, _args) end


---Returns true if the local player is in a multiplayer session.
---**Example Usage:**
---```lua
---network.is_session_started()
---```
function network.is_session_started() end


---Give the given pickup reward to the given player.
---**Example Usage:**
---```lua
---network.give_pickup_rewards(player, reward)
---```
---@param player integer Index of the player.
---@param reward integer Index of the reward pickup.
function network.give_pickup_rewards(player, reward) end



