---@meta

ITEMSET = {}
---@param p0 boolean
---@return ScrHandle
function ITEMSET.CREATE_ITEMSET(p0) end


---@param itemset ScrHandle
function ITEMSET.DESTROY_ITEMSET(itemset) end


---@param itemset ScrHandle
---@return boolean
function ITEMSET.IS_ITEMSET_VALID(itemset) end


---@param item ScrHandle
---@param itemset ScrHandle
---@return boolean
function ITEMSET.ADD_TO_ITEMSET(item, itemset) end


---@param item ScrHandle
---@param itemset ScrHandle
function ITEMSET.REMOVE_FROM_ITEMSET(item, itemset) end


---@param itemset ScrHandle
---@return int
function ITEMSET.GET_ITEMSET_SIZE(itemset) end


---@param index int
---@param itemset ScrHandle
---@return ScrHandle
function ITEMSET.GET_INDEXED_ITEM_IN_ITEMSET(index, itemset) end


---@param item ScrHandle
---@param itemset ScrHandle
---@return boolean
function ITEMSET.IS_IN_ITEMSET(item, itemset) end


---@param itemset ScrHandle
function ITEMSET.CLEAN_ITEMSET(itemset) end


