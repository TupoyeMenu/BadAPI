---@meta

RECORDING = {}
---@param p0 int
function RECORDING.REPLAY_START_EVENT(p0) end


function RECORDING.REPLAY_STOP_EVENT() end


function RECORDING.REPLAY_CANCEL_EVENT() end


---@param p0 float
---@param p1 float
---@param p2 int
function RECORDING.REPLAY_RECORD_BACK_FOR_TIME(p0, p1, p2) end


---@param missionNameLabel string
---@param p1 Any
function RECORDING.REPLAY_CHECK_FOR_EVENT_THIS_FRAME(missionNameLabel, p1) end


function RECORDING.REPLAY_PREVENT_RECORDING_THIS_FRAME() end


function RECORDING.REPLAY_RESET_EVENT_INFO() end


function RECORDING.REPLAY_DISABLE_CAMERA_MOVEMENT_THIS_FRAME() end


---@param p0 int
---@param p1 int
---@param p2 int
function RECORDING.RECORD_GREATEST_MOMENT(p0, p1, p2) end


---@param mode int
function RECORDING.START_REPLAY_RECORDING(mode) end


function RECORDING.STOP_REPLAY_RECORDING() end


function RECORDING.CANCEL_REPLAY_RECORDING() end


---@return boolean
function RECORDING.SAVE_REPLAY_RECORDING() end


---@return boolean
function RECORDING.IS_REPLAY_RECORDING() end


---@return boolean
function RECORDING.IS_REPLAY_INITIALIZED() end


---@return boolean
function RECORDING.IS_REPLAY_AVAILABLE() end


---@param p0 boolean
---@return boolean
function RECORDING.IS_REPLAY_RECORD_SPACE_AVAILABLE(p0) end


