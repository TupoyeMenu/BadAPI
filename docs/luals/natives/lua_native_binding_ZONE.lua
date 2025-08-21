---@meta

ZONE = {}
---@param x float
---@param y float
---@param z float
---@return int
function ZONE.GET_ZONE_AT_COORDS(x, y, z) end


---@param zoneName string
---@return int
function ZONE.GET_ZONE_FROM_NAME_ID(zoneName) end


---@param zoneId int
---@return int
function ZONE.GET_ZONE_POPSCHEDULE(zoneId) end


---@param x float
---@param y float
---@param z float
---@return string
function ZONE.GET_NAME_OF_ZONE(x, y, z) end


---@param zoneId int
---@param toggle boolean
function ZONE.SET_ZONE_ENABLED(zoneId, toggle) end


---@param zoneId int
---@return int
function ZONE.GET_ZONE_SCUMMINESS(zoneId) end


---@param scheduleId int
---@param vehicleHash Hash
function ZONE.OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(scheduleId, vehicleHash) end


---@param scheduleId int
function ZONE.CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(scheduleId) end


---@param x float
---@param y float
---@param z float
---@return Hash
function ZONE.GET_HASH_OF_MAP_AREA_AT_COORDS(x, y, z) end


