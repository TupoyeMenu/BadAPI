---@meta
---@alias BOOL boolean
---@alias float number
---@alias int integer
---@alias Hash integer
---@alias BlipHandle integer
---@alias CamHandle integer
---@alias EntityHandle integer
---@alias FireId integer
---@alias InteriorHandle integer
---@alias ObjectHandle integer
---@alias PedHandle integer
---@alias PickupHandle integer
---@alias PlayerHandle integer
---@alias ScrHandle integer
---@alias VehicleHandle integer
---@alias Any any
---@alias Vector3 vec3

LOBBY = {}
---@return boolean
function LOBBY.LOBBY_AUTO_MULTIPLAYER_MENU() end


---@return boolean
function LOBBY.LOBBY_AUTO_MULTIPLAYER_FREEMODE() end


---@param toggle BOOL
function LOBBY.LOBBY_SET_AUTO_MULTIPLAYER(toggle) end


---@return boolean
function LOBBY.LOBBY_AUTO_MULTIPLAYER_EVENT() end


---@param toggle BOOL
function LOBBY.LOBBY_SET_AUTO_MULTIPLAYER_EVENT(toggle) end


---@return boolean
function LOBBY.LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB() end


---@param toggle BOOL
function LOBBY.LOBBY_SET_AUTO_MP_RANDOM_JOB(toggle) end


---@param toggle BOOL
function LOBBY.SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(toggle) end


