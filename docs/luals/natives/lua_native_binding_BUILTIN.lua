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

BUILTIN = {}
---@param ms int
function BUILTIN.WAIT(ms) end


---@param scriptName string
---@param stackSize int
---@return int
function BUILTIN.START_NEW_SCRIPT(scriptName, stackSize) end


---@param scriptName string
---@param args number
---@param argCount int
---@param stackSize int
---@return int
function BUILTIN.START_NEW_SCRIPT_WITH_ARGS(scriptName, args, argCount, stackSize) end


---@param scriptHash Hash
---@param stackSize int
---@return int
function BUILTIN.START_NEW_SCRIPT_WITH_NAME_HASH(scriptHash, stackSize) end


---@param scriptHash Hash
---@param args number
---@param argCount int
---@param stackSize int
---@return int
function BUILTIN.START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(scriptHash, args, argCount, stackSize) end


---@return int
function BUILTIN.TIMERA() end


---@return int
function BUILTIN.TIMERB() end


---@param value int
function BUILTIN.SETTIMERA(value) end


---@param value int
function BUILTIN.SETTIMERB(value) end


---@return float
function BUILTIN.TIMESTEP() end


---@param value float
---@return float
function BUILTIN.SIN(value) end


---@param value float
---@return float
function BUILTIN.COS(value) end


---@param value float
---@return float
function BUILTIN.SQRT(value) end


---@param base float
---@param exponent float
---@return float
function BUILTIN.POW(base, exponent) end


---@param value float
---@return float
function BUILTIN.LOG10(value) end


---@param x float
---@param y float
---@param z float
---@return float
function BUILTIN.VMAG(x, y, z) end


---@param x float
---@param y float
---@param z float
---@return float
function BUILTIN.VMAG2(x, y, z) end


---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@return float
function BUILTIN.VDIST(x1, y1, z1, x2, y2, z2) end


---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@return float
function BUILTIN.VDIST2(x1, y1, z1, x2, y2, z2) end


---@param value int
---@param bitShift int
---@return int
function BUILTIN.SHIFT_LEFT(value, bitShift) end


---@param value int
---@param bitShift int
---@return int
function BUILTIN.SHIFT_RIGHT(value, bitShift) end


---@param value float
---@return int
function BUILTIN.FLOOR(value) end


---@param value float
---@return int
function BUILTIN.CEIL(value) end


---@param value float
---@return int
function BUILTIN.ROUND(value) end


---@param value int
---@return float
function BUILTIN.TO_FLOAT(value) end


---@param priority int
function BUILTIN.SET_THIS_THREAD_PRIORITY(priority) end


