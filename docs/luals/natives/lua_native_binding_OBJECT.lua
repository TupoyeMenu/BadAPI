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

OBJECT = {}
---@param modelHash Hash
---@param x float
---@param y float
---@param z float
---@param isNetwork boolean
---@param bScriptHostObj boolean
---@param dynamic boolean
---@return ObjectHandle
function OBJECT.CREATE_OBJECT(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic) end


---@param modelHash Hash
---@param x float
---@param y float
---@param z float
---@param isNetwork boolean
---@param bScriptHostObj boolean
---@param dynamic boolean
---@param p7 Any
---@return ObjectHandle
function OBJECT.CREATE_OBJECT_NO_OFFSET(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic, p7) end


---@param object ObjectHandle
function OBJECT.DELETE_OBJECT(object) end


---@param object ObjectHandle
---@return boolean
function OBJECT.PLACE_OBJECT_ON_GROUND_PROPERLY(object) end


---@param object ObjectHandle
---@return boolean
function OBJECT.PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(object) end


---@param object ObjectHandle
---@param p1 float
---@param p2 float
---@param p3 boolean
---@return boolean
function OBJECT.ROTATE_OBJECT(object, p1, p2, p3) end


---@param object ObjectHandle
---@param toX float
---@param toY float
---@param toZ float
---@param speedX float
---@param speedY float
---@param speedZ float
---@param collision boolean
---@return boolean
function OBJECT.SLIDE_OBJECT(object, toX, toY, toZ, speedX, speedY, speedZ, collision) end


---@param object ObjectHandle
---@param targettable boolean
---@param p2 Any
function OBJECT.SET_OBJECT_TARGETTABLE(object, targettable, p2) end


---@param object ObjectHandle
---@param setFlag34 boolean
---@param setFlag35 boolean
function OBJECT.SET_OBJECT_TARGETTABLE_BY_PLAYER_(object, setFlag34, setFlag35) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_OBJECT_FORCE_VEHICLES_TO_AVOID(object, toggle) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param modelHash Hash
---@param isMission boolean
---@param p6 boolean
---@param p7 boolean
---@return ObjectHandle
function OBJECT.GET_CLOSEST_OBJECT_OF_TYPE(x, y, z, radius, modelHash, isMission, p6, p7) end


---@param object ObjectHandle
---@param p1 Any
---@return boolean
function OBJECT.HAS_OBJECT_BEEN_BROKEN(object, p1) end


---@param p0 float
---@param p1 float
---@param p2 float
---@param p3 float
---@param modelHash Hash
---@param p5 Any
---@return boolean
function OBJECT.HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(p0, p1, p2, p3, modelHash, p5) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param modelHash Hash
---@param p5 boolean
---@return boolean
function OBJECT.HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(x, y, z, radius, modelHash, p5) end


---@param p0 Any
---@return boolean
function OBJECT.GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(p0) end


---@param xPos float
---@param yPos float
---@param zPos float
---@param heading float
---@param xOffset float
---@param yOffset float
---@param zOffset float
---@return Vector3
function OBJECT.GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(xPos, yPos, zPos, heading, xOffset, yOffset, zOffset) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param modelHash Hash
---@param outPosition Vector3
---@param outRotation Vector3
---@param rotationOrder int
---@return boolean
---@return Vector3 outPosition
---@return Vector3 outRotation
function OBJECT.GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(x, y, z, radius, modelHash, outPosition, outRotation, rotationOrder) end


---@param type Hash
---@param x float
---@param y float
---@param z float
---@param locked boolean
---@param heading float
---@param p6 boolean
function OBJECT.SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(type, x, y, z, locked, heading, p6) end


---@param type Hash
---@param x float
---@param y float
---@param z float
---@param locked boolean
---@param heading float
---@return boolean locked
---@return float heading
function OBJECT.GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(type, x, y, z, locked, heading) end


---@param modelHash Hash
---@param x float
---@param y float
---@param z float
---@param locked boolean
---@param xRotMult float
---@param yRotMult float
---@param zRotMult float
function OBJECT.SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(modelHash, x, y, z, locked, xRotMult, yRotMult, zRotMult) end


---@param p0 Any
function OBJECT.PLAY_OBJECT_AUTO_START_ANIM(p0) end


---@param doorHash Hash
---@param modelHash Hash
---@param x float
---@param y float
---@param z float
---@param p5 boolean
---@param scriptDoor boolean
---@param isLocal boolean
---@param p8 Any
function OBJECT.ADD_DOOR_TO_SYSTEM(doorHash, modelHash, x, y, z, p5, scriptDoor, isLocal, p8) end


---@param doorHash Hash
---@param p1 Any
function OBJECT.REMOVE_DOOR_FROM_SYSTEM(doorHash, p1) end


---@param doorHash Hash
---@param state int
---@param requestDoor boolean
---@param forceUpdate boolean
function OBJECT.DOOR_SYSTEM_SET_DOOR_STATE(doorHash, state, requestDoor, forceUpdate) end


---@param doorHash Hash
---@return int
function OBJECT.DOOR_SYSTEM_GET_DOOR_STATE(doorHash) end


---@param doorHash Hash
---@return int
function OBJECT.DOOR_SYSTEM_GET_DOOR_PENDING_STATE(doorHash) end


---@param doorHash Hash
---@param rate float
---@param requestDoor boolean
---@param forceUpdate boolean
function OBJECT.DOOR_SYSTEM_SET_AUTOMATIC_RATE(doorHash, rate, requestDoor, forceUpdate) end


---@param doorHash Hash
---@param distance float
---@param requestDoor boolean
---@param forceUpdate boolean
function OBJECT.DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(doorHash, distance, requestDoor, forceUpdate) end


---@param doorHash Hash
---@param ajar float
---@param requestDoor boolean
---@param forceUpdate boolean
function OBJECT.DOOR_SYSTEM_SET_OPEN_RATIO(doorHash, ajar, requestDoor, forceUpdate) end


---@param doorHash Hash
---@return float
function OBJECT.DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(doorHash) end


---@param doorHash Hash
---@return float
function OBJECT.DOOR_SYSTEM_GET_OPEN_RATIO(doorHash) end


---@param doorHash Hash
---@return boolean
function OBJECT.DOOR_SYSTEM_GET_IS_SPRING_REMOVED(doorHash) end


---@param doorHash Hash
---@param removed boolean
---@param requestDoor boolean
---@param forceUpdate boolean
function OBJECT.DOOR_SYSTEM_SET_SPRING_REMOVED(doorHash, removed, requestDoor, forceUpdate) end


---@param doorHash Hash
---@param toggle boolean
function OBJECT.DOOR_SYSTEM_SET_HOLD_OPEN(doorHash, toggle) end


---@param doorHash Hash
---@param p1 boolean
function OBJECT.DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(doorHash, p1) end


---@param doorHash Hash
---@return boolean
function OBJECT.IS_DOOR_REGISTERED_WITH_SYSTEM(doorHash) end


---@param doorHash Hash
---@return boolean
function OBJECT.IS_DOOR_CLOSED(doorHash) end


---@param p0 boolean
function OBJECT.OPEN_ALL_BARRIERS_FOR_RACE(p0) end


function OBJECT.CLOSE_ALL_BARRIERS_FOR_RACE() end


---@param p0 Any
---@return boolean
function OBJECT.DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(p0) end


---@param x float
---@param y float
---@param z float
---@param modelHash Hash
---@param outDoorHash Hash
---@return boolean
---@return Hash outDoorHash
function OBJECT.DOOR_SYSTEM_FIND_EXISTING_DOOR(x, y, z, modelHash, outDoorHash) end


---@param garageHash Hash
---@param p1 boolean
---@param p2 int
---@return boolean
function OBJECT.IS_GARAGE_EMPTY(garageHash, p1, p2) end


---@param garageHash Hash
---@param player PlayerHandle
---@param p2 float
---@param p3 int
---@return boolean
function OBJECT.IS_PLAYER_ENTIRELY_INSIDE_GARAGE(garageHash, player, p2, p3) end


---@param garageHash Hash
---@param player PlayerHandle
---@param p2 int
---@return boolean
function OBJECT.IS_PLAYER_PARTIALLY_INSIDE_GARAGE(garageHash, player, p2) end


---@param garageHash Hash
---@param p1 boolean
---@param p2 boolean
---@param p3 boolean
---@param p4 Any
---@return boolean
function OBJECT.ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(garageHash, p1, p2, p3, p4) end


---@param garageHash Hash
---@param p1 boolean
---@param p2 boolean
---@param p3 boolean
---@param p4 Any
---@return boolean
function OBJECT.IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(garageHash, p1, p2, p3, p4) end


---@param garageHash Hash
---@param entity EntityHandle
---@param p2 float
---@param p3 int
---@return boolean
function OBJECT.IS_OBJECT_ENTIRELY_INSIDE_GARAGE(garageHash, entity, p2, p3) end


---@param garageHash Hash
---@param entity EntityHandle
---@param p2 int
---@return boolean
function OBJECT.IS_OBJECT_PARTIALLY_INSIDE_GARAGE(garageHash, entity, p2) end


---@param garageHash Hash
---@param isNetwork boolean
function OBJECT.CLEAR_GARAGE(garageHash, isNetwork) end


---@param garageHash Hash
---@param vehicles boolean
---@param peds boolean
---@param objects boolean
---@param isNetwork boolean
function OBJECT.CLEAR_OBJECTS_INSIDE_GARAGE(garageHash, vehicles, peds, objects, isNetwork) end


---@param id int
---@param toggle boolean
function OBJECT.DISABLE_TIDYING_UP_IN_GARAGE(id, toggle) end


---@param garageHash Hash
---@param toggle boolean
function OBJECT.ENABLE_SAVING_IN_GARAGE(garageHash, toggle) end


function OBJECT.CLOSE_SAFEHOUSE_GARAGES() end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param hash Hash
---@param p5 boolean
---@return boolean
function OBJECT.DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(x, y, z, radius, hash, p5) end


---@param xPos float
---@param yPos float
---@param zPos float
---@param x1 float
---@param y1 float
---@param z1 float
---@param x2 float
---@param y2 float
---@param z2 float
---@param width float
---@param debug boolean
---@param includeZ boolean
---@return boolean
function OBJECT.IS_POINT_IN_ANGLED_AREA(xPos, yPos, zPos, x1, y1, z1, x2, y2, z2, width, debug, includeZ) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(object, toggle) end


---@param object ObjectHandle
---@param weight float
---@param p2 float
---@param p3 float
---@param p4 float
---@param p5 float
---@param gravity float
---@param p7 float
---@param p8 float
---@param p9 float
---@param p10 float
---@param buoyancy float
function OBJECT.SET_OBJECT_PHYSICS_PARAMS(object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy) end


---@param p0 Any
---@param p1 boolean
---@return float
function OBJECT.GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(p0, p1) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(object, toggle) end


---@param x float
---@param y float
---@param z float
---@param range float
---@param p4 boolean
---@return boolean
function OBJECT.IS_ANY_OBJECT_NEAR_POINT(x, y, z, range, p4) end


---@param objectHash Hash
---@param x float
---@param y float
---@param z float
---@param range float
---@return boolean
function OBJECT.IS_OBJECT_NEAR_POINT(objectHash, x, y, z, range) end


---@param object ObjectHandle
function OBJECT.REMOVE_OBJECT_HIGH_DETAIL_MODEL(object) end


---@param p0 ObjectHandle
---@param p1 Any
---@param p2 boolean
function OBJECT.BREAK_OBJECT_FRAGMENT_CHILD(p0, p1, p2) end


---@param p0 Any
---@param p1 Any
---@param p2 Any
function OBJECT.DAMAGE_OBJECT_FRAGMENT_CHILD(p0, p1, p2) end


---@param object ObjectHandle
function OBJECT.FIX_OBJECT_FRAGMENT(object) end


---@param object ObjectHandle
function OBJECT.TRACK_OBJECT_VISIBILITY(object) end


---@param object ObjectHandle
---@return boolean
function OBJECT.IS_OBJECT_VISIBLE(object) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_OBJECT_IS_SPECIAL_GOLFBALL(object, toggle) end


---@param p0 Any
---@param p1 boolean
function OBJECT.SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(p0, p1) end


---@param value boolean
function OBJECT.ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(value) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(object, toggle) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param name string
---@return ObjectHandle
function OBJECT.GET_RAYFIRE_MAP_OBJECT(x, y, z, radius, name) end


---@param object ObjectHandle
---@param state int
function OBJECT.SET_STATE_OF_RAYFIRE_MAP_OBJECT(object, state) end


---@param object ObjectHandle
---@return int
function OBJECT.GET_STATE_OF_RAYFIRE_MAP_OBJECT(object) end


---@param object ObjectHandle
---@return boolean
function OBJECT.DOES_RAYFIRE_MAP_OBJECT_EXIST(object) end


---@param object ObjectHandle
---@return float
function OBJECT.GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(object) end


---@param pickupHash Hash
---@param posX float
---@param posY float
---@param posZ float
---@param p4 int
---@param value int
---@param p6 boolean
---@param modelHash Hash
---@return PickupHandle
function OBJECT.CREATE_PICKUP(pickupHash, posX, posY, posZ, p4, value, p6, modelHash) end


---@param pickupHash Hash
---@param posX float
---@param posY float
---@param posZ float
---@param rotX float
---@param rotY float
---@param rotZ float
---@param flag int
---@param amount int
---@param p9 Any
---@param p10 boolean
---@param modelHash Hash
---@return PickupHandle
function OBJECT.CREATE_PICKUP_ROTATE(pickupHash, posX, posY, posZ, rotX, rotY, rotZ, flag, amount, p9, p10, modelHash) end


function OBJECT.FORCE_PICKUP_ROTATE_FACE_UP() end


---@param pickupHash Hash
---@param pickup PickupHandle
function OBJECT.SET_CUSTOM_PICKUP_WEAPON_HASH(pickupHash, pickup) end


---@param pickupHash Hash
---@param posX float
---@param posY float
---@param posZ float
---@param flags int
---@param value int
---@param modelHash Hash
---@param p7 boolean
---@param p8 boolean
---@return ObjectHandle
function OBJECT.CREATE_AMBIENT_PICKUP(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8) end


---@param pickupHash Hash
---@param posX float
---@param posY float
---@param posZ float
---@param flags int
---@param value int
---@param modelHash Hash
---@param p7 boolean
---@param p8 boolean
---@return ObjectHandle
function OBJECT.CREATE_NON_NETWORKED_AMBIENT_PICKUP(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8) end


---@param p0 Any
---@param p1 Any
function OBJECT.BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(p0, p1) end


---@param pickupHash Hash
---@param x float
---@param y float
---@param z float
---@param placeOnGround boolean
---@param modelHash Hash
---@return ObjectHandle
function OBJECT.CREATE_PORTABLE_PICKUP(pickupHash, x, y, z, placeOnGround, modelHash) end


---@param pickupHash Hash
---@param x float
---@param y float
---@param z float
---@param placeOnGround boolean
---@param modelHash Hash
---@return ObjectHandle
function OBJECT.CREATE_NON_NETWORKED_PORTABLE_PICKUP(pickupHash, x, y, z, placeOnGround, modelHash) end


---@param pickupObject ObjectHandle
---@param ped PedHandle
function OBJECT.ATTACH_PORTABLE_PICKUP_TO_PED(pickupObject, ped) end


---@param pickupObject ObjectHandle
function OBJECT.DETACH_PORTABLE_PICKUP_FROM_PED(pickupObject) end


---@param object ObjectHandle
function OBJECT.FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(object) end


---@param pickupObject ObjectHandle
---@param toggle boolean
function OBJECT.HIDE_PORTABLE_PICKUP_WHEN_DETACHED(pickupObject, toggle) end


---@param modelHash Hash
---@param number int
function OBJECT.SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(modelHash, number) end


---@param toggle boolean
function OBJECT.SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(toggle) end


---@param x float
---@param y float
---@param z float
---@param p3 float
---@param p4 float
---@return Vector3
function OBJECT.GET_SAFE_PICKUP_COORDS(x, y, z, p3, p4) end


---@param x float
---@param y float
---@param z float
---@param radius float
function OBJECT.ADD_EXTENDED_PICKUP_PROBE_AREA(x, y, z, radius) end


function OBJECT.CLEAR_EXTENDED_PICKUP_PROBE_AREAS() end


---@param pickup PickupHandle
---@return Vector3
function OBJECT.GET_PICKUP_COORDS(pickup) end


---@param p0 Any
---@param p1 Any
function OBJECT.SUPPRESS_PICKUP_SOUND_FOR_PICKUP(p0, p1) end


---@param pickupHash Hash
function OBJECT.REMOVE_ALL_PICKUPS_OF_TYPE(pickupHash) end


---@param pickup PickupHandle
---@return boolean
function OBJECT.HAS_PICKUP_BEEN_COLLECTED(pickup) end


---@param pickup PickupHandle
function OBJECT.REMOVE_PICKUP(pickup) end


---@param x float
---@param y float
---@param z float
---@param value int
---@param amount int
---@param model Hash
function OBJECT.CREATE_MONEY_PICKUPS(x, y, z, value, amount, model) end


---@param pickup PickupHandle
---@return boolean
function OBJECT.DOES_PICKUP_EXIST(pickup) end


---@param pickupObject ObjectHandle
---@return boolean
function OBJECT.DOES_PICKUP_OBJECT_EXIST(pickupObject) end


---@param pickup PickupHandle
---@return ObjectHandle
function OBJECT.GET_PICKUP_OBJECT(pickup) end


---@param object ObjectHandle
---@return boolean
function OBJECT.IS_OBJECT_A_PICKUP(object) end


---@param object ObjectHandle
---@return boolean
function OBJECT.IS_OBJECT_A_PORTABLE_PICKUP(object) end


---@param pickupHash Hash
---@param x float
---@param y float
---@param z float
---@param radius float
---@return boolean
function OBJECT.DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(pickupHash, x, y, z, radius) end


---@param pickup PickupHandle
---@param duration int
function OBJECT.SET_PICKUP_REGENERATION_TIME(pickup, duration) end


---@param p0 Any
function OBJECT.FORCE_PICKUP_REGENERATE(p0) end


---@param player PlayerHandle
---@param pickupHash Hash
---@param toggle boolean
function OBJECT.SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(player, pickupHash, toggle) end


---@param modelHash Hash
---@param toggle boolean
function OBJECT.SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(modelHash, toggle) end


---@param pickupHash Hash
function OBJECT.ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(pickupHash) end


---@param object ObjectHandle
---@param p1 Any
---@param p2 boolean
function OBJECT.SET_TEAM_PICKUP_OBJECT(object, p1, p2) end


---@param object ObjectHandle
---@param p1 boolean
---@param p2 boolean
function OBJECT.PREVENT_COLLECTION_OF_PORTABLE_PICKUP(object, p1, p2) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_GLOW_DISABLED_(pickup, toggle) end


---@param pickup PickupHandle
---@param p1 float
function OBJECT.SET_PICKUP_GLOW_OFFSET(pickup, p1) end


---@param pickup PickupHandle
---@param p1 float
---@param p2 boolean
function OBJECT.SET_PICKUP_OBJECT_GLOW_OFFSET(pickup, p1, p2) end


---@param pickup PickupHandle
function OBJECT.SET_OBJECT_GLOW_IN_SAME_TEAM(pickup) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_OBJECT_ARROW_MARKER(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(pickup, toggle) end


---@param pickupHash Hash
---@return int
function OBJECT.GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(pickupHash) end


---@param multiplier float
function OBJECT.SET_PICKUP_GENERATION_RANGE_MULTIPLIER(multiplier) end


---@return float
function OBJECT.GET_PICKUP_GENERATION_RANGE_MULTIPLIER() end


---@param p0 boolean
function OBJECT.SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(p0) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_UNCOLLECTABLE(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(pickup, toggle) end


---@param p0 int
function OBJECT.SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(p0) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PORTABLE_PICKUP_PERSIST(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(pickup, toggle) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.ALLOW_PICKUP_BY_NONE_PARTICIPANT(pickup, toggle) end


---@param rewardType int
---@param suppress boolean
function OBJECT.SUPPRESS_PICKUP_REWARD_TYPE(rewardType, suppress) end


function OBJECT.CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION() end


---@param rewardType int
function OBJECT.CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(rewardType) end


---@param x float
---@param y float
---@param z float
---@param colorIndex int
function OBJECT.RENDER_FAKE_PICKUP_GLOW(x, y, z, colorIndex) end


---@param pickup PickupHandle
function OBJECT.SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(pickup) end


---@param pickup PickupHandle
---@param toggle boolean
function OBJECT.SET_PICKUP_TRACK_DAMAGE_EVENTS(pickup, toggle) end


---@param entity EntityHandle
---@param toggle boolean
function OBJECT.SET_ENTITY_FLAG_SUPPRESS_SHADOW(entity, toggle) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(object, toggle) end


---@param pickupHash Hash
---@return Hash
function OBJECT.GET_WEAPON_TYPE_FROM_PICKUP_TYPE(pickupHash) end


---@param weaponHash Hash
---@return Hash
function OBJECT.GET_PICKUP_TYPE_FROM_WEAPON_HASH(weaponHash) end


---@param object ObjectHandle
---@return boolean
function OBJECT.IS_PICKUP_WEAPON_OBJECT_VALID(object) end


---@param object ObjectHandle
---@return int
function OBJECT.GET_OBJECT_TINT_INDEX(object) end


---@param object ObjectHandle
---@param textureVariation int
function OBJECT.SET_OBJECT_TINT_INDEX(object, textureVariation) end


---@param x float
---@param y float
---@param z float
---@param radius float
---@param modelHash Hash
---@param textureVariation int
---@return boolean
function OBJECT.SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(x, y, z, radius, modelHash, textureVariation) end


---@param p0 Any
---@param p1 Any
function OBJECT.SET_PROP_TINT_INDEX(p0, p1) end


---@param object ObjectHandle
---@param p1 boolean
---@param r int
---@param g int
---@param b int
---@return boolean
function OBJECT.SET_PROP_LIGHT_COLOR(object, p1, r, g, b) end


---@param object ObjectHandle
---@return boolean
function OBJECT.IS_PROP_LIGHT_OVERRIDEN(object) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_OBJECT_IS_VISIBLE_IN_MIRRORS(object, toggle) end


---@param object ObjectHandle
---@param p1 Any
function OBJECT.SET_OBJECT_SPEED_BOOST_AMOUNT(object, p1) end


---@param object ObjectHandle
---@param duration float
function OBJECT.SET_OBJECT_SPEED_BOOST_DURATION(object, duration) end


---@param pickupHash Hash
---@return Hash
function OBJECT.CONVERT_OLD_PICKUP_TYPE_TO_NEW(pickupHash) end


---@param x float
---@param y float
---@param z float
---@param p3 float
function OBJECT.SET_FORCE_OBJECT_THIS_FRAME(x, y, z, p3) end


---@param object ObjectHandle
function OBJECT.ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(object) end


---@param p0 Any
function OBJECT.SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(p0) end


---@param entity EntityHandle
---@param p1 Any
function OBJECT.SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(entity, p1) end


---@param object ObjectHandle
---@param toggle boolean
---@param p2 int
function OBJECT.SET_DRIVE_ARTICULATED_JOINT(object, toggle, p2) end


---@param object ObjectHandle
---@param toggle boolean
---@param p2 int
---@param ped PedHandle
function OBJECT.SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(object, toggle, p2, ped) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_OBJECT_IS_A_PRESSURE_PLATE(object, toggle) end


---@param object ObjectHandle
---@param p1 boolean
function OBJECT.SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(object, p1) end


---@param object ObjectHandle
---@param p1 Any
---@return boolean
function OBJECT.GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(object, p1) end


---@param p0 Any
---@param p1 Any
---@return boolean
function OBJECT.GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(p0, p1) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_IS_OBJECT_ARTICULATED(object, toggle) end


---@param object ObjectHandle
---@param toggle boolean
function OBJECT.SET_IS_OBJECT_BALL(object, toggle) end


