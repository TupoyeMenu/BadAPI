---@meta

DLC = {}
---@return boolean
function DLC.ARE_ANY_CCS_PENDING() end


---@param dlcHash Hash
---@return boolean
function DLC.IS_DLC_PRESENT(dlcHash) end


---@return boolean
function DLC.DLC_CHECK_CLOUD_DATA_CORRECT() end


---@return int
function DLC.GET_EXTRACONTENT_CLOUD_RESULT() end


---@return boolean
function DLC.DLC_CHECK_COMPAT_PACK_CONFIGURATION() end


---@return boolean
function DLC.GET_EVER_HAD_BAD_PACK_ORDER() end


---@return boolean
function DLC.GET_IS_LOADING_SCREEN_ACTIVE() end


---@return boolean
function DLC.GET_IS_INITIAL_LOADING_SCREEN_ACTIVE() end


---@param p0 boolean
---@param unused int
---@return boolean
---@return boolean p0
function DLC.HAS_CLOUD_REQUESTS_FINISHED(p0, unused) end


function DLC.ON_ENTER_SP() end


function DLC.ON_ENTER_MP() end


