---@meta
---Class representing a text_select object.
---@class text_select
text_select = {}
-- Constructors (1)

---Returns: text_select: An instance of text_select.
---**Example Usage:**
---```lua
---myInstance = text_select:new(getLineAtIdx, getNumLines, enableWordWrap)
---```
---@param getLineAtIdx function Function taking a line number and returning the string in that line
---@param getNumLines function Function returning the total number of lines of text
---@param enableWordWrap boolean
---@return text_select
function text_select:new(getLineAtIdx, getNumLines, enableWordWrap) end

-- Functions (4)

---Checks if there is an active selection in the text.
---**Example Usage:**
---```lua
---boolean = text_select:hasSelection()
---```
---@return boolean 
function text_select:hasSelection() end


---Copies the selected text to the clipboard.
---**Example Usage:**
---```lua
---text_select:copy()
---```
function text_select:copy() end


---Selects all text in the window.
---**Example Usage:**
---```lua
---text_select:selectAll()
---```
function text_select:selectAll() end


---Draws the text selection rectangle and handles user input.
---**Example Usage:**
---```lua
---text_select:update()
---```
function text_select:update() end



