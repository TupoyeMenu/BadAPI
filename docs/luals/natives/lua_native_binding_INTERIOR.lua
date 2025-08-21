---@meta

INTERIOR = {}
---@param interior InteriorHandle
---@return float
function INTERIOR.GET_INTERIOR_HEADING(interior) end


---@param interior InteriorHandle
---@param position Vector3
---@param nameHash Hash
---@return Vector3 position
---@return Hash nameHash
function INTERIOR.GET_INTERIOR_LOCATION_AND_NAMEHASH(interior, position, nameHash) end


---@param interior InteriorHandle
---@return int
function INTERIOR.GET_INTERIOR_GROUP_ID(interior) end


---@param interior InteriorHandle
---@param x float
---@param y float
---@param z float
---@return Vector3
function INTERIOR.GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(interior, x, y, z) end


---@return boolean
function INTERIOR.IS_INTERIOR_SCENE() end


---@param interior InteriorHandle
---@return boolean
function INTERIOR.IS_VALID_INTERIOR(interior) end


---@param entity EntityHandle
function INTERIOR.CLEAR_ROOM_FOR_ENTITY(entity) end


---@param entity EntityHandle
---@param interior InteriorHandle
---@param roomHashKey Hash
function INTERIOR.FORCE_ROOM_FOR_ENTITY(entity, interior, roomHashKey) end


---@param entity EntityHandle
---@return Hash
function INTERIOR.GET_ROOM_KEY_FROM_ENTITY(entity) end


---@param entity EntityHandle
---@return Hash
function INTERIOR.GET_KEY_FOR_ENTITY_IN_ROOM(entity) end


---@param entity EntityHandle
---@return InteriorHandle
function INTERIOR.GET_INTERIOR_FROM_ENTITY(entity) end


---@param entity EntityHandle
---@param interior InteriorHandle
function INTERIOR.RETAIN_ENTITY_IN_INTERIOR(entity, interior) end


---@param entity EntityHandle
function INTERIOR.CLEAR_INTERIOR_STATE_OF_ENTITY(entity) end


---@param p0 Any
---@param p1 Any
function INTERIOR.FORCE_ACTIVATING_TRACKING_ON_ENTITY(p0, p1) end


---@param interiorID int
---@param roomHashKey Hash
function INTERIOR.FORCE_ROOM_FOR_GAME_VIEWPORT(interiorID, roomHashKey) end


---@param roomName string
function INTERIOR.SET_ROOM_FOR_GAME_VIEWPORT_BY_NAME(roomName) end


---@param roomHashKey Hash
function INTERIOR.SET_ROOM_FOR_GAME_VIEWPORT_BY_KEY(roomHashKey) end


---@return Hash
function INTERIOR.GET_ROOM_KEY_FOR_GAME_VIEWPORT() end


function INTERIOR.CLEAR_ROOM_FOR_GAME_VIEWPORT() end


---@return InteriorHandle
function INTERIOR.GET_INTERIOR_FROM_PRIMARY_VIEW() end


---@param x float
---@param y float
---@param z float
---@return InteriorHandle
function INTERIOR.GET_INTERIOR_AT_COORDS(x, y, z) end


---@param pickup PickupHandle
---@param roomName string
function INTERIOR.ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pickup, roomName) end


---@param interior InteriorHandle
function INTERIOR.PIN_INTERIOR_IN_MEMORY(interior) end


---@param interior InteriorHandle
function INTERIOR.UNPIN_INTERIOR(interior) end


---@param interior InteriorHandle
---@return boolean
function INTERIOR.IS_INTERIOR_READY(interior) end


---@param interior InteriorHandle
---@return boolean
function INTERIOR.SET_INTERIOR_IN_USE(interior) end


---@param x float
---@param y float
---@param z float
---@param interiorType string
---@return InteriorHandle
function INTERIOR.GET_INTERIOR_AT_COORDS_WITH_TYPE(x, y, z, interiorType) end


---@param x float
---@param y float
---@param z float
---@param typeHash Hash
---@return InteriorHandle
function INTERIOR.GET_INTERIOR_AT_COORDS_WITH_TYPEHASH(x, y, z, typeHash) end


function INTERIOR.ACTIVATE_INTERIOR_GROUPS_USING_CAMERA() end


---@param x float
---@param y float
---@param z float
---@return boolean
function INTERIOR.IS_COLLISION_MARKED_OUTSIDE(x, y, z) end


---@param x float
---@param y float
---@param z float
---@return InteriorHandle
function INTERIOR.GET_INTERIOR_FROM_COLLISION(x, y, z) end


---@param toggle boolean
function INTERIOR.ENABLE_STADIUM_PROBES_THIS_FRAME(toggle) end


---@param interior InteriorHandle
---@param entitySetName string
function INTERIOR.ACTIVATE_INTERIOR_ENTITY_SET(interior, entitySetName) end


---@param interior InteriorHandle
---@param entitySetName string
function INTERIOR.DEACTIVATE_INTERIOR_ENTITY_SET(interior, entitySetName) end


---@param interior InteriorHandle
---@param entitySetName string
---@return boolean
function INTERIOR.IS_INTERIOR_ENTITY_SET_ACTIVE(interior, entitySetName) end


---@param interior InteriorHandle
---@param entitySetName string
---@param color int
function INTERIOR.SET_INTERIOR_ENTITY_SET_TINT_INDEX(interior, entitySetName, color) end


---@param interior InteriorHandle
function INTERIOR.REFRESH_INTERIOR(interior) end


---@param mapObjectHash Hash
function INTERIOR.ENABLE_EXTERIOR_CULL_MODEL_THIS_FRAME(mapObjectHash) end


---@param mapObjectHash Hash
function INTERIOR.ENABLE_SHADOW_CULL_MODEL_THIS_FRAME(mapObjectHash) end


---@param interior InteriorHandle
---@param toggle boolean
function INTERIOR.DISABLE_INTERIOR(interior, toggle) end


---@param interior InteriorHandle
---@return boolean
function INTERIOR.IS_INTERIOR_DISABLED(interior) end


---@param interior InteriorHandle
---@param toggle boolean
function INTERIOR.CAP_INTERIOR(interior, toggle) end


---@param interior InteriorHandle
---@return boolean
function INTERIOR.IS_INTERIOR_CAPPED(interior) end


---@param toggle boolean
function INTERIOR.DISABLE_METRO_SYSTEM(toggle) end


---@param entity EntityHandle
---@param toggle boolean
function INTERIOR.SET_IS_EXTERIOR_ONLY(entity, toggle) end


