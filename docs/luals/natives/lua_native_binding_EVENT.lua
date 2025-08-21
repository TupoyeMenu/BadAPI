---@meta

EVENT = {}
---@param ped PedHandle
---@param name Hash
function EVENT.SET_DECISION_MAKER(ped, name) end


---@param name Hash
---@param eventType int
function EVENT.CLEAR_DECISION_MAKER_EVENT_RESPONSE(name, eventType) end


---@param name Hash
---@param eventType int
function EVENT.BLOCK_DECISION_MAKER_EVENT(name, eventType) end


---@param name Hash
---@param eventType int
function EVENT.UNBLOCK_DECISION_MAKER_EVENT(name, eventType) end


---@param eventType int
---@param x float
---@param y float
---@param z float
---@param duration float
---@return int
function EVENT.ADD_SHOCKING_EVENT_AT_POSITION(eventType, x, y, z, duration) end


---@param eventType int
---@param entity EntityHandle
---@param duration float
---@return int
function EVENT.ADD_SHOCKING_EVENT_FOR_ENTITY(eventType, entity, duration) end


---@param eventType int
---@param x float
---@param y float
---@param z float
---@param radius float
---@return boolean
function EVENT.IS_SHOCKING_EVENT_IN_SPHERE(eventType, x, y, z, radius) end


---@param event ScrHandle
---@return boolean
function EVENT.REMOVE_SHOCKING_EVENT(event) end


---@param p0 boolean
function EVENT.REMOVE_ALL_SHOCKING_EVENTS(p0) end


function EVENT.REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS() end


function EVENT.SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME() end


---@param eventType int
function EVENT.SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(eventType) end


function EVENT.SUPPRESS_AGITATION_EVENTS_NEXT_FRAME() end


