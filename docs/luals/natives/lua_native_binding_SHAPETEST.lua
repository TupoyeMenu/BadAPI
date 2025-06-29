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

SHAPETEST = {}
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param flags int
---@param entity EntityHandle
---@param p8 int
---@return int
function SHAPETEST.START_SHAPE_TEST_LOS_PROBE(x1, y1, z1, x2, y2, z2, flags, entity, p8) end


---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param flags int
---@param entity EntityHandle
---@param p8 int
---@return int
function SHAPETEST.START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(x1, y1, z1, x2, y2, z2, flags, entity, p8) end


---@param entity EntityHandle
---@param flags1 int
---@param flags2 int
---@return int
function SHAPETEST.START_SHAPE_TEST_BOUNDING_BOX(entity, flags1, flags2) end


---@param x float
---@param y float
---@param z float
---@param dimX float
---@param dimY float
---@param dimZ float
---@param rotX float
---@param rotY float
---@param rotZ float
---@param p9 Any
---@param flags int
---@param entity EntityHandle
---@param p12 Any
---@return int
function SHAPETEST.START_SHAPE_TEST_BOX(x, y, z, dimX, dimY, dimZ, rotX, rotY, rotZ, p9, flags, entity, p12) end


---@param entity EntityHandle
---@param flags1 int
---@param flags2 int
---@return int
function SHAPETEST.START_SHAPE_TEST_BOUND(entity, flags1, flags2) end


---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param radius float
---@param flags int
---@param entity EntityHandle
---@param p9 int
---@return int
function SHAPETEST.START_SHAPE_TEST_CAPSULE(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9) end


---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param radius float
---@param flags int
---@param entity EntityHandle
---@param p9 Any
---@return int
function SHAPETEST.START_SHAPE_TEST_SWEPT_SPHERE(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9) end


---@param pVec1 Vector3
---@param pVec2 Vector3
---@param flag int
---@param entity EntityHandle
---@param flag2 int
---@return int
---@return Vector3 pVec1
---@return Vector3 pVec2
function SHAPETEST.START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(pVec1, pVec2, flag, entity, flag2) end


---@param shapeTestHandle int
---@param hit boolean
---@param endCoords Vector3
---@param surfaceNormal Vector3
---@param entityHit EntityHandle
---@return int
---@return boolean hit
---@return Vector3 endCoords
---@return Vector3 surfaceNormal
---@return EntityHandle entityHit
function SHAPETEST.GET_SHAPE_TEST_RESULT(shapeTestHandle, hit, endCoords, surfaceNormal, entityHit) end


---@param shapeTestHandle int
---@param hit boolean
---@param endCoords Vector3
---@param surfaceNormal Vector3
---@param materialHash Hash
---@param entityHit EntityHandle
---@return int
---@return boolean hit
---@return Vector3 endCoords
---@return Vector3 surfaceNormal
---@return Hash materialHash
---@return EntityHandle entityHit
function SHAPETEST.GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(shapeTestHandle, hit, endCoords, surfaceNormal, materialHash, entityHit) end


---@param entityHit EntityHandle
function SHAPETEST.RELEASE_SCRIPT_GUID_FROM_ENTITY(entityHit) end


