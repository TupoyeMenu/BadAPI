---@meta

DECORATOR = {}
---@param entity EntityHandle
---@param propertyName string
---@param timestamp int
---@return boolean
function DECORATOR.DECOR_SET_TIME(entity, propertyName, timestamp) end


---@param entity EntityHandle
---@param propertyName string
---@param value boolean
---@return boolean
function DECORATOR.DECOR_SET_BOOL(entity, propertyName, value) end


---@param entity EntityHandle
---@param propertyName string
---@param value float
---@return boolean
function DECORATOR.DECOR_SET_FLOAT(entity, propertyName, value) end


---@param entity EntityHandle
---@param propertyName string
---@param value int
---@return boolean
function DECORATOR.DECOR_SET_INT(entity, propertyName, value) end


---@param entity EntityHandle
---@param propertyName string
---@return boolean
function DECORATOR.DECOR_GET_BOOL(entity, propertyName) end


---@param entity EntityHandle
---@param propertyName string
---@return float
function DECORATOR.DECOR_GET_FLOAT(entity, propertyName) end


---@param entity EntityHandle
---@param propertyName string
---@return int
function DECORATOR.DECOR_GET_INT(entity, propertyName) end


---@param entity EntityHandle
---@param propertyName string
---@return boolean
function DECORATOR.DECOR_EXIST_ON(entity, propertyName) end


---@param entity EntityHandle
---@param propertyName string
---@return boolean
function DECORATOR.DECOR_REMOVE(entity, propertyName) end


---@param propertyName string
---@param type int
function DECORATOR.DECOR_REGISTER(propertyName, type) end


---@param propertyName string
---@param type int
---@return boolean
function DECORATOR.DECOR_IS_REGISTERED_AS_TYPE(propertyName, type) end


function DECORATOR.DECOR_REGISTER_LOCK() end


