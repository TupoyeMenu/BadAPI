---@meta

APP = {}
---@return boolean
function APP.APP_DATA_VALID() end


---@param property string
---@return int
function APP.APP_GET_INT(property) end


---@param property string
---@return float
function APP.APP_GET_FLOAT(property) end


---@param property string
---@return string
function APP.APP_GET_STRING(property) end


---@param property string
---@param value int
function APP.APP_SET_INT(property, value) end


---@param property string
---@param value float
function APP.APP_SET_FLOAT(property, value) end


---@param property string
---@param value string
function APP.APP_SET_STRING(property, value) end


---@param appName string
function APP.APP_SET_APP(appName) end


---@param blockName string
function APP.APP_SET_BLOCK(blockName) end


function APP.APP_CLEAR_BLOCK() end


function APP.APP_CLOSE_APP() end


function APP.APP_CLOSE_BLOCK() end


---@return boolean
function APP.APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT() end


---@param appName string
---@return boolean
function APP.APP_HAS_SYNCED_DATA(appName) end


function APP.APP_SAVE_DATA() end


---@return int
function APP.APP_GET_DELETED_FILE_STATUS() end


---@param appName string
---@return boolean
function APP.APP_DELETE_APP_DATA(appName) end


