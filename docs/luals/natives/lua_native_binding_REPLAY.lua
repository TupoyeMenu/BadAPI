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

REPLAY = {}
---@param p0 string
---@param p1 BOOL
function REPLAY.REGISTER_EFFECT_FOR_REPLAY_EDITOR(p0, p1) end


---@return boolean
function REPLAY.REPLAY_SYSTEM_HAS_REQUESTED_A_SCRIPT_CLEANUP() end


function REPLAY.SET_SCRIPTS_HAVE_CLEANED_UP_FOR_REPLAY_SYSTEM() end


---@param p0 BOOL
function REPLAY.SET_REPLAY_SYSTEM_PAUSED_FOR_SAVE(p0) end


function REPLAY.REPLAY_CONTROL_SHUTDOWN() end


---@param p0 int
function REPLAY.ACTIVATE_ROCKSTAR_EDITOR(p0) end


