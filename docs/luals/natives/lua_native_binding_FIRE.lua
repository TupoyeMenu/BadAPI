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

FIRE = {}
---@param X float
---@param Y float
---@param Z float
---@param maxChildren int
---@param isGasFire boolean
---@return FireId
function FIRE.START_SCRIPT_FIRE(X, Y, Z, maxChildren, isGasFire) end


---@param fireHandle FireId
function FIRE.REMOVE_SCRIPT_FIRE(fireHandle) end


---@param entity EntityHandle
---@return FireId
function FIRE.START_ENTITY_FIRE(entity) end


---@param entity EntityHandle
function FIRE.STOP_ENTITY_FIRE(entity) end


---@param entity EntityHandle
---@return boolean
function FIRE.IS_ENTITY_ON_FIRE(entity) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@return int
function FIRE.GET_NUMBER_OF_FIRES_IN_RANGE(x, y, z, radius) end


---@param p0 float
function FIRE.SET_FLAMMABILITY_MULTIPLIER(p0) end


---@param x float
---@param y float
---@param z float
---@param radius float
function FIRE.STOP_FIRE_IN_RANGE(x, y, z, radius) end


---@param outPosition Vector3
---@param x float
---@param y float
---@param z float
---@return boolean
---@return Vector3 outPosition
function FIRE.GET_CLOSEST_FIRE_POS(outPosition, x, y, z) end


---@param x float
---@param y float
---@param z float
---@param explosionType int
---@param damageScale float
---@param isAudible boolean
---@param isInvisible boolean
---@param cameraShake float
---@param noDamage boolean
function FIRE.ADD_EXPLOSION(x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake, noDamage) end


---@param ped PedHandle
---@param x float
---@param y float
---@param z float
---@param explosionType int
---@param damageScale float
---@param isAudible boolean
---@param isInvisible boolean
---@param cameraShake float
function FIRE.ADD_OWNED_EXPLOSION(ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake) end


---@param x float
---@param y float
---@param z float
---@param explosionType int
---@param explosionFx Hash
---@param damageScale float
---@param isAudible boolean
---@param isInvisible boolean
---@param cameraShake float
function FIRE.ADD_EXPLOSION_WITH_USER_VFX(x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake) end


---@param explosionType int
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@return boolean
function FIRE.IS_EXPLOSION_IN_AREA(explosionType, x1, y1, z1, x2, y2, z2) end


---@param explosionType int
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@return boolean
function FIRE.IS_EXPLOSION_ACTIVE_IN_AREA(explosionType, x1, y1, z1, x2, y2, z2) end


---@param explosionType int
---@param x float
---@param y float
---@param z float
---@param radius float
---@return boolean
function FIRE.IS_EXPLOSION_IN_SPHERE(explosionType, x, y, z, radius) end


---@param explosionType int
---@param x float
---@param y float
---@param z float
---@param radius float
---@return EntityHandle
function FIRE.GET_OWNER_OF_EXPLOSION_IN_SPHERE(explosionType, x, y, z, radius) end


---@param explosionType int
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param width float
---@return boolean
function FIRE.IS_EXPLOSION_IN_ANGLED_AREA(explosionType, x1, y1, z1, x2, y2, z2, width) end


---@param explosionType int
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param radius float
---@return EntityHandle
function FIRE.GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(explosionType, x1, y1, z1, x2, y2, z2, radius) end


