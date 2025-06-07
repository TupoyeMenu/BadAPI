---@meta
---@class memory
---Table containing helper functions related to process memory.
memory = {}
-- Functions (5)

---Scans the specified memory pattern within the "GTA5.exe" module and returns a pointer to the found address.
---**Example Usage:**
---```lua
---pointer = memory.scan_pattern(pattern)
---```
---@param pattern string byte pattern (IDA format)
---@return pointer A pointer to the found address.
function memory.scan_pattern(pattern) end


---**Example Usage:**
---```lua
---pointer = memory.handle_to_ptr(entity)
---```
---@param entity number script game entity handle
---@return pointer A rage::CDynamicEntity pointer to the script game entity handle
function memory.handle_to_ptr(entity) end


---**Example Usage:**
---```lua
---number = memory.ptr_to_handle(mem_addr)
---```
---@param mem_addr pointer A rage::CDynamicEntity pointer.
---@return number The script game entity handle linked to the given rage::CDynamicEntity pointer.
function memory.ptr_to_handle(mem_addr) end


---**Example Usage:**
---```lua
---pointer = memory.allocate(size)
---```
---@param size integer The number of bytes to allocate on the heap.
---@return pointer A pointer to the newly allocated memory.
function memory.allocate(size) end


---**Example Usage:**
---```lua
---memory.free(ptr)
---```
---@param ptr pointer The pointer that must be freed.
function memory.free(ptr) end



