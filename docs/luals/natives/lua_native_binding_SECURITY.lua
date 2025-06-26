---@meta
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

SECURITY = {}
---@param variable number
function SECURITY.REGISTER_SCRIPT_VARIABLE(variable) end


---@param variable number
function SECURITY.UNREGISTER_SCRIPT_VARIABLE(variable) end


function SECURITY.FORCE_CHECK_SCRIPT_VARIABLES() end


