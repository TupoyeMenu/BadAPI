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

SAVEMIGRATION = {}
---@return boolean
function SAVEMIGRATION.SAVEMIGRATION_IS_MP_ENABLED() end


---@return boolean
function SAVEMIGRATION.SAVEMIGRATION_MP_REQUEST_ACCOUNTS() end


---@return int
function SAVEMIGRATION.SAVEMIGRATION_MP_GET_ACCOUNTS_STATUS() end


---@return int
function SAVEMIGRATION.SAVEMIGRATION_MP_NUM_ACCOUNTS() end


---@param p0 int
---@param p1 number
---@return boolean
function SAVEMIGRATION.SAVEMIGRATION_MP_GET_ACCOUNT(p0, p1) end


---@return boolean
function SAVEMIGRATION.SAVEMIGRATION_MP_REQUEST_STATUS() end


---@return int
function SAVEMIGRATION.SAVEMIGRATION_MP_GET_STATUS() end


