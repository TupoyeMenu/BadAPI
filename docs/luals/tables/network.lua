---@meta
---@class network
---Table containing helper functions for network related features.
network = {}
-- Functions (5)

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


---**Example Usage:**
---```lua
---integer = network.get_selected_player()
---```
---@return integer Returns the index of the currently selected player in the GUI.
function network.get_selected_player() end


---**Example Usage:**
---```lua
---boolean = network.is_player_flagged_as_modder(player_idx)
---```
---@param player_idx integer Index of the player.
---@return boolean Returns true if the given player is flagged as a modder.
function network.is_player_flagged_as_modder(player_idx) end



