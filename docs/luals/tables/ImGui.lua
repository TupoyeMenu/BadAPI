---@meta
---@alias ImDrawList any
---@alias ImGuiTableSortSpecs any

--#region ImGui Enums

---@enum ImGuiDir
ImGuiDir =
{
	None = -1,
	Left = 0,
	Right = 1,
	Up = 2,
	Down = 3,
	COUNT = 4,
}

---@enum ImGuiTreeNodeFlags
ImGuiTreeNodeFlags =
{
	None                 = nil,
	Selected             = nil, -- Draw as selected
	Framed               = nil, -- Draw frame with background (e.g. for CollapsingHeader)
	AllowOverlap         = nil, -- Hit testing to allow subsequent widgets to overlap this one
	NoTreePushOnOpen     = nil, -- Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
	NoAutoOpenOnLog      = nil, -- Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
	DefaultOpen          = nil, -- Default node to be open
	OpenOnDoubleClick    = nil, -- Open on double-click instead of simple click (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
	OpenOnArrow          = nil, -- Open when clicking on the arrow part (default for multi-select unless any _OpenOnXXX behavior is set explicitly). Both behaviors may be combined.
	Leaf                 = nil, -- No collapsing, no arrow (use as a convenience for leaf nodes).
	Bullet               = nil, -- Display a bullet instead of arrow. IMPORTANT: node can still be marked open/close if you don't set the _Leaf flag!
	FramePadding         = nil, -- Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding() before the node.
	SpanAvailWidth       = nil, -- Extend hit box to the right-most edge, even if not framed. This is not the default in order to allow adding other items on the same line without using AllowOverlap mode.
	SpanFullWidth        = nil, -- Extend hit box to the left-most and right-most edges (cover the indent area).
	SpanLabelWidth       = nil, -- Narrow hit box + narrow hovering highlight, will only cover the label text.
	SpanAllColumns       = nil, -- Frame will span all columns of its container table (label will still fit in current column)
	LabelSpanAllColumns  = nil, -- Label will span all columns of its container table
	NavLeftJumpsToParent = nil, -- Nav: left arrow moves back to parent. This is processed in TreePop() when there's an unfullfilled Left nav request remaining.

	CollapsingHeader     = nil,

	DrawLinesNone        = nil, -- No lines drawn
	DrawLinesFull        = nil, -- Horizontal lines to child nodes. Vertical line drawn down to TreePop() position: cover full contents. Faster (for large trees).
	DrawLinesToNodes     = nil, -- Horizontal lines to child nodes. Vertical line drawn down to bottom-most child node. Slower (for large trees).
}

---@enum ImGuiSelectableFlags
ImGuiSelectableFlags =
{
	None               = 0,
	NoAutoClosePopups  = nil, -- Clicking this doesn't close parent popup window (overrides ImGuiItemFlags_AutoClosePopups)
	SpanAllColumns     = nil, -- Frame will span all columns of its container table (text will still fit in current column)
	AllowDoubleClick   = nil, -- Generate press events on double clicks too
	Disabled           = nil, -- Cannot be selected, display grayed out text
	AllowOverlap       = nil, -- (WIP) Hit testing to allow subsequent widgets to overlap this one
	Highlight          = nil, -- Make the item be displayed as if it is hovered
}

---@enum ImGuiPopupFlags
ImGuiPopupFlags =
{
	None                    = 0,
	MouseButtonLeft         = 0,  -- For BeginPopupContext*(): open on Left Mouse release. Guaranteed to always be == 0 (same as ImGuiMouseButton_Left)
	MouseButtonRight        = 1,  -- For BeginPopupContext*(): open on Right Mouse release. Guaranteed to always be == 1 (same as ImGuiMouseButton_Right)
	MouseButtonMiddle       = 2,  -- For BeginPopupContext*(): open on Middle Mouse release. Guaranteed to always be == 2 (same as ImGuiMouseButton_Middle)
	MouseButtonMask_        = 0x1F,
	MouseButtonDefault_     = 1,
	NoReopen                = nil, -- For OpenPopup*(), BeginPopupContext*(): don't reopen same popup if already open (won't reposition, won't reinitialize navigation)
	NoOpenOverExistingPopup = nil, -- For OpenPopup*(), BeginPopupContext*(): don't open if there's already a popup at the same level of the popup stack
	NoOpenOverItems         = nil, -- For BeginPopupContextWindow(): don't return true when hovering items, only when hovering empty space
	AnyPopupId              = nil, -- For IsPopupOpen(): ignore the ImGuiID parameter and test for any popup.
	AnyPopupLevel           = nil, -- For IsPopupOpen(): search/test at any level of the popup stack (default test in the current level)
	AnyPopup                = nil,
}

---@enum ImGuiTableColumnFlags
ImGuiTableColumnFlags =
{
	None                 = nil,
	Disabled             = nil, -- Overriding/master disable flag: hide column, won't show in context menu (unlike calling TableSetColumnEnabled() which manipulates the user accessible state)
	DefaultHide          = nil, -- Default as a hidden/disabled column.
	DefaultSort          = nil, -- Default as a sorting column.
	WidthStretch         = nil, -- Column will stretch. Preferable with horizontal scrolling disabled (default if table sizing policy is _SizingStretchSame or _SizingStretchProp).
	WidthFixed           = nil, -- Column will not stretch. Preferable with horizontal scrolling enabled (default if table sizing policy is _SizingFixedFit and table is resizable).
	NoResize             = nil, -- Disable manual resizing.
	NoReorder            = nil, -- Disable manual reordering this column, this will also prevent other columns from crossing over this column.
	NoHide               = nil, -- Disable ability to hide/disable this column.
	NoClip               = nil, -- Disable clipping for this column (all NoClip columns will render in a same draw command).
	NoSort               = nil, -- Disable ability to sort on this field (even if ImGuiTableFlags_Sortable is set on the table).
	NoSortAscending      = nil, -- Disable ability to sort in the ascending direction.
	NoSortDescending     = nil, -- Disable ability to sort in the descending direction.
	NoHeaderLabel        = nil, -- TableHeadersRow() will submit an empty label for this column. Convenient for some small columns. Name will still appear in context menu or in angled headers. You may append into this cell by calling TableSetColumnIndex() right after the TableHeadersRow() call.
	NoHeaderWidth        = nil, -- Disable header text width contribution to automatic column width.
	PreferSortAscending  = nil, -- Make the initial sort direction Ascending when first sorting on this column (default).
	PreferSortDescending = nil, -- Make the initial sort direction Descending when first sorting on this column.
	IndentEnable         = nil, -- Use current Indent value when entering cell (default for column 0).
	IndentDisable        = nil, -- Ignore current Indent value when entering cell (default for columns > 0). Indentation changes _within_ the cell will still be honored.
	AngledHeader         = nil, -- TableHeadersRow() will submit an angled header row for this column. Note this will add an extra row.
	IsEnabled            = nil, -- Status: is enabled == not hidden by user/api (referred to as "Hide" in _DefaultHide and _NoHide) flags.
	IsVisible            = nil, -- Status: is visible == is enabled AND not clipped by scrolling.
	IsSorted             = nil, -- Status: is currently part of the sort specs
	IsHovered            = nil, -- Status: is hovered by mouse

	-- [Internal] Combinations and masks
	WidthMask_           = nil,
	IndentMask_          = nil,
	StatusMask_          = nil,
	NoDirectResize_      = nil, -- [Internal] Disable user resizing this column directly (it may however we resized indirectly from its left edge)
}

---@enum ImGuiChildFlags
ImGuiChildFlags =
{
	None                   = nil,
	Borders                = nil, -- Show an outer border and enable WindowPadding. (IMPORTANT: this is always == 1 == true for legacy reason)
	AlwaysUseWindowPadding = nil, -- Pad with style.WindowPadding even if no border are drawn (no padding by default for non-bordered child windows because it makes more sense)
	ResizeX                = nil, -- Allow resize from right border (layout direction). Enable .ini saving (unless ImGuiWindowFlags_NoSavedSettings passed to window flags)
	ResizeY                = nil, -- Allow resize from bottom border (layout direction). "
	AutoResizeX            = nil, -- Enable auto-resizing width. Read "IMPORTANT: Size measurement" details above.
	AutoResizeY            = nil, -- Enable auto-resizing height. Read "IMPORTANT: Size measurement" details above.
	AlwaysAutoResize       = nil, -- Combined with AutoResizeX/AutoResizeY. Always measure size even when child is hidden, always return true, always disable clipping optimization! NOT RECOMMENDED.
	FrameStyle             = nil, -- Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding.
	NavFlattened           = nil, -- [BETA] Share focus scope, allow keyboard/gamepad navigation to cross over parent border to this child or between sibling child windows.
}

---@enum ImGuiWindowFlags
ImGuiWindowFlags =
{
	None                          = nil,
	NoTitleBar                    = nil, -- Disable title-bar
	NoResize                      = nil, -- Disable user resizing with the lower-right grip
	NoMove                        = nil, -- Disable user moving the window
	NoScrollbar                   = nil, -- Disable scrollbars (window can still scroll with mouse or programmatically)
	NoScrollWithMouse             = nil, -- Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	NoCollapse                    = nil, -- Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
	AlwaysAutoResize              = nil, -- Resize every window to its content every frame
	NoBackground                  = nil, -- Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	NoSavedSettings               = nil, -- Never load/save settings in .ini file
	NoMouseInputs                 = nil, -- Disable catching mouse, hovering test with pass through.
	MenuBar                       = nil, -- Has a menu-bar
	HorizontalScrollbar           = nil, -- Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	NoFocusOnAppearing            = nil, -- Disable taking focus when transitioning from hidden to visible state
	NoBringToFrontOnFocus         = nil, -- Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	AlwaysVerticalScrollbar       = nil, -- Always show vertical scrollbar (even if ContentSize.y < Size.y)
	AlwaysHorizontalScrollbar     = nil, -- Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	NoNavInputs                   = nil, -- No keyboard/gamepad navigation within the window
	NoNavFocus                    = nil, -- No focusing toward this window with keyboard/gamepad navigation (e.g. skipped by CTRL+TAB)
	UnsavedDocument               = nil, -- Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
	NoDocking                     = nil, -- Disable docking of this window
	NoNav                         = nil,
	NoDecoration                  = nil,
	NoInputs                      = nil,

	-- [Internal]
	DockNodeHost = nil,        -- Don't use! For internal use by Begin()/NewFrame()
	ChildWindow  = nil,        -- Don't use! For internal use by BeginChild()
	Tooltip      = nil,        -- Don't use! For internal use by BeginTooltip()
	Popup        = nil,        -- Don't use! For internal use by BeginPopup()
	Modal        = nil,        -- Don't use! For internal use by BeginPopupModal()
	ChildMenu    = nil,        -- Don't use! For internal use by BeginMenu()
}

---@enum ImGuiConfigFlags
ImGuiConfigFlags =
{
	None                   = 0,
	NavEnableKeyboard      = nil, -- Master keyboard navigation enable flag. Enable full Tabbing + directional arrows + space/enter to activate.
	NavEnableGamepad       = nil, -- Master gamepad navigation enable flag. Backend also needs to set ImGuiBackendFlags_HasGamepad.
	NoMouse                = nil, -- Instruct dear imgui to disable mouse inputs and interactions.
	NoMouseCursorChange    = nil, -- Instruct backend to not alter mouse cursor shape and visibility. Use if the backend cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.
	NoKeyboard             = nil, -- Instruct dear imgui to disable keyboard inputs and interactions. This is done by ignoring keyboard events and clearing existing states.
	DockingEnable          = nil, -- Docking enable flags.
	ViewportsEnable        = nil, -- Viewport enable flags (require both ImGuiBackendFlags_PlatformHasViewports + ImGuiBackendFlags_RendererHasViewports set by the respective backends)
	IsSRGB                 = nil, -- Application is SRGB-aware.
	IsTouchScreen          = nil, -- Application is using a touch screen instead of a mouse.
}

---@enum ImGuiBackendFlags
ImGuiBackendFlags =
{
	None                  = 0,
	HasGamepad            = nil, -- Backend Platform supports gamepad and currently has one connected.
	HasMouseCursors       = nil, -- Backend Platform supports honoring GetMouseCursor() value to change the OS cursor shape.
	HasSetMousePos        = nil, -- Backend Platform supports io.WantSetMousePos requests to reposition the OS mouse position (only used if io.ConfigNavMoveSetMousePos is set).
	RendererHasVtxOffset  = nil, -- Backend Renderer supports ImDrawCmd::VtxOffset. This enables output of large meshes (64K+ vertices) while still using 16-bit indices.
	RendererHasTextures   = nil, -- Backend Renderer supports ImTextureData requests to create/update/destroy textures. This enables incremental texture updates and texture reloads. See https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md for instructions on how to upgrade your custom backend.
	PlatformHasViewports  = nil, -- Backend Platform supports multiple viewports.
	HasMouseHoveredViewport=nil, -- Backend Platform supports calling io.AddMouseViewportEvent() with the viewport under the mouse. IF POSSIBLE, ignore viewports with the ImGuiViewportFlags_NoInputs flag (Win32 backend, GLFW 3.30+ backend can do this, SDL backend cannot). If this cannot be done, Dear ImGui needs to use a flawed heuristic to find the viewport under.
	RendererHasViewports  = nil, -- Backend Renderer supports multiple viewports.
}

---@enum ImGuiCol
ImGuiCol =
{
	Text = nil,
	TextDisabled = nil,
	WindowBg = nil, -- Background of normal windows
	ChildBg = nil, -- Background of child windows
	PopupBg = nil, -- Background of popups, menus, tooltips windows
	Border = nil,
	BorderShadow = nil,
	FrameBg = nil, -- Background of checkbox, radio button, plot, slider, text input
	FrameBgHovered = nil,
	FrameBgActive = nil,
	TitleBg = nil,       -- Title bar
	TitleBgActive = nil, -- Title bar when focused
	TitleBgCollapsed = nil, -- Title bar when collapsed
	MenuBarBg = nil,
	ScrollbarBg = nil,
	ScrollbarGrab = nil,
	ScrollbarGrabHovered = nil,
	ScrollbarGrabActive = nil,
	CheckMark = nil, -- Checkbox tick and RadioButton circle
	SliderGrab = nil,
	SliderGrabActive = nil,
	Button = nil,
	ButtonHovered = nil,
	ButtonActive = nil,
	Header = nil, -- Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
	HeaderHovered = nil,
	HeaderActive = nil,
	Separator = nil,
	SeparatorHovered = nil,
	SeparatorActive = nil,
	ResizeGrip = nil, -- Resize grip in lower-right and lower-left corners of windows.
	ResizeGripHovered = nil,
	ResizeGripActive = nil,
	InputTextCursor = nil,        -- InputText cursor/caret
	TabHovered = nil,             -- Tab background, when hovered
	Tab = nil,                    -- Tab background, when tab-bar is focused & tab is unselected
	TabSelected = nil,            -- Tab background, when tab-bar is focused & tab is selected
	TabSelectedOverline = nil,    -- Tab horizontal overline, when tab-bar is focused & tab is selected
	TabDimmed = nil,              -- Tab background, when tab-bar is unfocused & tab is unselected
	TabDimmedSelected = nil,      -- Tab background, when tab-bar is unfocused & tab is selected
	TabDimmedSelectedOverline = nil, --..horizontal overline, when tab-bar is unfocused & tab is selected
	DockingPreview = nil,         -- Preview overlay color when about to docking something
	DockingEmptyBg = nil,         -- Background color for empty node (e.g. CentralNode with no window docked into it)
	PlotLines = nil,
	PlotLinesHovered = nil,
	PlotHistogram = nil,
	PlotHistogramHovered = nil,
	TableHeaderBg = nil,      -- Table header background
	TableBorderStrong = nil,  -- Table outer and header borders (prefer using Alpha=1.0 here)
	TableBorderLight = nil,   -- Table inner borders (prefer using Alpha=1.0 here)
	TableRowBg = nil,         -- Table row background (even rows)
	TableRowBgAlt = nil,      -- Table row background (odd rows)
	TextLink = nil,           -- Hyperlink color
	TextSelectedBg = nil,     -- Selected text inside an InputText
	TreeLines = nil,          -- Tree node hierarchy outlines when using ImGuiTreeNodeFlags_DrawLines
	DragDropTarget = nil,     -- Rectangle highlighting a drop target
	NavCursor = nil,          -- Color of keyboard/gamepad navigation cursor/rectangle, when visible
	NavWindowingHighlight = nil, -- Highlight window when using CTRL+TAB
	NavWindowingDimBg = nil,  -- Darken/colorize entire screen behind the CTRL+TAB window list, when active
	ModalWindowDimBg = nil,   -- Darken/colorize entire screen behind a modal window, when one is active
	COUNT = nil,
}

---@enum ImGuiMouseSource
ImGuiMouseSource =
{
	Mouse = nil, -- Input is coming from an actual mouse.
	TouchScreen = nil, -- Input is coming from a touch screen (no hovering prior to initial press, less precise initial press aiming, dual-axis wheeling possible).
	Pen = nil, -- Input is coming from a pressure/magnetic pen (often used in conjunction with high-sampling rates).
}

---@enum ImGuiCond
ImGuiCond =
{
	None          = nil, -- No condition (always set the variable), same as _Always
	Always        = nil, -- No condition (always set the variable), same as _None
	Once          = nil, -- Set the variable once per runtime session (only the first call will succeed)
	FirstUseEver  = nil, -- Set the variable if the object/window has no persistently saved data (no entry in .ini file)
	Appearing     = nil, -- Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
}

---@enum ImGuiInputTextFlags
ImGuiInputTextFlags =
{
	-- Basic filters (also see ImGuiInputTextFlags_CallbackCharFilter)
	None                = 0,
	CharsDecimal        = nil,   -- Allow 0123456789.+-*/
	CharsHexadecimal    = nil,   -- Allow 0123456789ABCDEFabcdef
	CharsScientific     = nil,   -- Allow 0123456789.+-*/eE (Scientific notation input)
	CharsUppercase      = nil,   -- Turn a..z into A..Z
	CharsNoBlank        = nil,   -- Filter out spaces, tabs

	-- Inputs
	AllowTabInput       = nil, -- Pressing TAB input a '\t' character into the text field
	EnterReturnsTrue    = nil, -- Return 'true' when Enter is pressed (as opposed to every time the value was modified). Consider using IsItemDeactivatedAfterEdit() instead!
	EscapeClearsAll     = nil, -- Escape key clears content if not empty, and deactivate otherwise (contrast to default behavior of Escape to revert)
	CtrlEnterForNewLine = nil, -- In multi-line mode, validate with Enter, add new line with Ctrl+Enter (default is opposite: validate with Ctrl+Enter, add line with Enter).

	-- Other options
	ReadOnly            = nil,  -- Read-only mode
	Password            = nil,  -- Password mode, display all characters as '*', disable copy
	AlwaysOverwrite     = nil,  -- Overwrite mode
	AutoSelectAll       = nil,  -- Select entire text when first taking mouse focus
	ParseEmptyRefVal    = nil,  -- InputFloat(), InputInt(), InputScalar() etc. only: parse empty string as zero value.
	DisplayEmptyRefVal  = nil,  -- InputFloat(), InputInt(), InputScalar() etc. only: when value is zero, do not display it. Generally used with ImGuiInputTextFlags_ParseEmptyRefVal.
	NoHorizontalScroll  = nil,  -- Disable following the cursor horizontally
	NoUndoRedo          = nil,  -- Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().

	-- Elide display / Alignment
	ElideLeft           = nil,  -- When text doesn't fit, elide left side to ensure right side stays visible. Useful for path/filenames. Single-line only!

	-- Callback features
	CallbackCompletion  = nil, -- Callback on pressing TAB (for completion handling)
	CallbackHistory     = nil, -- Callback on pressing Up/Down arrows (for history handling)
	CallbackAlways      = nil, -- Callback on each iteration. User code may query cursor position, modify text buffer.
	CallbackCharFilter  = nil, -- Callback on character inputs to replace or discard them. Modify 'EventChar' to replace or discard, or return 1 in callback to discard.
	CallbackResize      = nil, -- Callback on buffer capacity changes request (beyond 'buf_size' parameter value), allowing the string to grow. Notify when the string wants to be resized (for string types which hold a cache of their Size). You will be provided a new BufSize in the callback and NEED to honor it. (see misc/cpp/imgui_stdlib.h for an example of using this)
	CallbackEdit        = nil, -- Callback on any edit. Note that InputText() already returns true on edit + you can always use IsItemEdited(). The callback is useful to manipulate the underlying buffer while focus is active.
}

---@enum ImGuiStyleVar
ImGuiStyleVar =
{
    Alpha = nil,                    -- float
    DisabledAlpha = nil,            -- float
    WindowPadding = nil,            -- ImVec2
    WindowRounding = nil,           -- float
    WindowBorderSize = nil,         -- float
    WindowMinSize = nil,            -- ImVec2
    WindowTitleAlign = nil,         -- ImVec2
    ChildRounding = nil,            -- float
    ChildBorderSize = nil,          -- float
    PopupRounding = nil,            -- float
    PopupBorderSize = nil,          -- float
    FramePadding = nil,             -- ImVec2
    FrameRounding = nil,            -- float
    FrameBorderSize = nil,          -- float
    ItemSpacing = nil,              -- ImVec2
    ItemInnerSpacing = nil,         -- ImVec2
    IndentSpacing = nil,            -- float
    CellPadding = nil,              -- ImVec2
    ScrollbarSize = nil,            -- float
    ScrollbarRounding = nil,        -- float
    GrabMinSize = nil,              -- float
    GrabRounding = nil,             -- float
    ImageBorderSize = nil,          -- float
    TabRounding = nil,              -- float
    TabBorderSize = nil,            -- float
    TabBarBorderSize = nil,         -- float
    TabBarOverlineSize = nil,       -- float
    TableAngledHeadersAngle = nil,  -- float
    TableAngledHeadersTextAlign = nil, -- ImVec2
    TreeLinesSize = nil,            -- float
    TreeLinesRounding = nil,        -- float
    ButtonTextAlign = nil,          -- ImVec2
    SelectableTextAlign = nil,      -- ImVec2
    SeparatorTextBorderSize = nil,  -- float
    SeparatorTextAlign = nil,       -- ImVec2
    SeparatorTextPadding = nil,     -- ImVec2
    DockingSeparatorSize = nil,     -- float
}

---@enum ImGuiItemFlags
ImGuiItemFlags =
{
	None = nil,
	NoTabStop = nil, -- Disable keyboard tabbing. This is a "lighter" version of ImGuiItemFlags_NoNav.
	NoNav = nil, -- Disable any form of focusing (keyboard/gamepad directional navigation and SetKeyboardFocusHere() calls).
	NoNavDefaultFocus = nil, -- Disable item being a candidate for default focus (e.g. used by title bar items).
	ButtonRepeat = nil, -- Any button-like behavior will have repeat mode enabled (based on io.KeyRepeatDelay and io.KeyRepeatRate values). Note that you can also call IsItemActive() after any button to tell if it is being held.
	AutoClosePopups = nil, -- MenuItem()/Selectable() automatically close their parent popup window.
	AllowDuplicateId = nil, -- Allow submitting an item with the same identifier as an item already submitted this frame without triggering a warning tooltip if io.ConfigDebugHighlightIdConflicts is set.
};

---@enum ImGuiDockNodeFlags
ImGuiDockNodeFlags =
{
	None = nil,
	KeepAliveOnly = nil, -- Don't display the dockspace node but keep it alive. Windows docked into this dockspace node won't be undocked.
	NoDockingOverCentralNode = nil, -- Disable docking over the Central Node, which will be always kept empty.
	PassthruCentralNode = nil, -- Enable passthru dockspace: 1) DockSpace() will render a ImGuiCol_WindowBg background covering everything excepted the Central Node when empty. Meaning the host window should probably use SetNextWindowBgAlpha(0.0f) prior to Begin() when using this. 2) When Central Node is empty: let inputs pass-through + won't display a DockingEmptyBg background. See demo for details.
	NoDockingSplit = nil, -- Disable other windows/nodes from splitting this node.
	NoResize = nil, -- Disable resizing node using the splitter/separators. Useful with programmatically setup dockspaces.
	AutoHideTabBar = nil, -- Tab bar will automatically hide when there is a single window in the dock node.
	NoUndocking = nil -- Disable undocking this node.
}

---@enum ImGuiSliderFlags
ImGuiSliderFlags =
{
	None = nil,
	Logarithmic = nil, -- Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
	NoRoundToFormat = nil, -- Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits).
	NoInput = nil, -- Disable CTRL+Click or Enter key allowing to input text directly into the widget.
	WrapAround = nil, -- Enable wrapping around from max to min and from min to max. Only supported by DragXXX() functions for now.
	ClampOnInput = nil, -- Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.
	ClampZeroRange = nil, -- Clamp even if min==max==0.0f. Otherwise due to legacy reason DragXXX functions don't clamp with those values. When your clamping limits are dynamic you almost always want to use it.
	NoSpeedTweaks = nil, -- Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic.
	AlwaysClamp = nil,
}

---@enum ImGuiComboFlags
ImGuiComboFlags =
{
	None = nil,
	PopupAlignLeft = nil, -- Align the popup toward the left by default
	HeightSmall = nil, -- Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
	HeightRegular = nil, -- Max ~8 items visible (default)
	HeightLarge = nil, -- Max ~20 items visible
	HeightLargest = nil, -- As many fitting items as possible
	NoArrowButton = nil, -- Display on the preview box without the square arrow button
	NoPreview = nil, -- Display only a square arrow button
	WidthFitPreview = nil, -- Width dynamically calculated from preview contents
	HeightMask = nil,
}


---@enum ImGuiHoveredFlags
ImGuiHoveredFlags =
{
	None = nil, -- Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
	ChildWindows                  = nil, -- IsWindowHovered() only: Return true if any children of the window is hovered
	RootWindow                    = nil, -- IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
	AnyWindow                     = nil, -- IsWindowHovered() only: Return true if any window is hovered
	NoPopupHierarchy              = nil, -- IsWindowHovered() only: Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
	DockHierarchy                 = nil, -- IsWindowHovered() only: Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
	AllowWhenBlockedByPopup       = nil, -- Return true even if a popup window is normally blocking access to this item/window
	AllowWhenBlockedByActiveItem  = nil, -- Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
	AllowWhenOverlappedByItem     = nil, -- IsItemHovered() only: Return true even if the item uses AllowOverlap mode and is overlapped by another hoverable item.
	AllowWhenOverlappedByWindow   = nil, -- IsItemHovered() only: Return true even if the position is obstructed or overlapped by another window.
	AllowWhenDisabled             = nil, -- IsItemHovered() only: Return true even if the item is disabled
	NoNavOverride                 = nil, -- IsItemHovered() only: Disable using keyboard/gamepad navigation state when active, always query mouse
	AllowWhenOverlapped           = nil,
	RectOnly                      = nil,
	RootAndChildWindows           = nil,

	-- Tooltips mode
	-- - typically used in IsItemHovered() + SetTooltip() sequence.
	-- - this is a shortcut to pull flags from 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' where you can reconfigure desired behavior.
	--   e.g. 'TooltipHoveredFlagsForMouse' defaults to 'ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_DelayShort'.
	-- - for frequently actioned or hovered items providing a tooltip, you want may to use ImGuiHoveredFlags_ForTooltip (stationary + delay) so the tooltip doesn't show too often.
	-- - for items which main purpose is to be hovered, or items with low affordance, or in less consistent apps, prefer no delay or shorter delay.
	ForTooltip                    = nil,  -- Shortcut for standard flags when using IsItemHovered() + SetTooltip() sequence.

	-- (Advanced) Mouse Hovering delays.
	-- - generally you can use ImGuiHoveredFlags_ForTooltip to use application-standardized flags.
	-- - use those if you need specific overrides.
	Stationary                    = nil,  -- Require mouse to be stationary for style.HoverStationaryDelay (~0.15 sec) _at least one time_. After this, can move on same item/window. Using the stationary test tends to reduces the need for a long delay.
	DelayNone                     = nil,  -- IsItemHovered() only: Return true immediately (default). As this is the default you generally ignore this.
	DelayShort                    = nil,  -- IsItemHovered() only: Return true after style.HoverDelayShort elapsed (~0.15 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
	DelayNormal                   = nil,  -- IsItemHovered() only: Return true after style.HoverDelayNormal elapsed (~0.40 sec) (shared between items) + requires mouse to be stationary for style.HoverStationaryDelay (once per item).
	NoSharedDelay                 = nil,  -- IsItemHovered() only: Disable shared delay system where moving from one item to the next keeps the previous timer for a short time (standard for tooltips with long delays)
}

---@enum ImGuiFocusedFlags
ImGuiFocusedFlags =
{
	None                          = nil,
	ChildWindows                  = nil, -- Return true if any children of the window is focused
	RootWindow                    = nil, -- Test from root window (top most parent of the current hierarchy)
	AnyWindow                     = nil, -- Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
	NoPopupHierarchy              = nil, -- Do not consider popup hierarchy (do not treat popup emitter as parent of popup) (when used with _ChildWindows or _RootWindow)
	DockHierarchy                 = nil, -- Consider docking hierarchy (treat dockspace host as parent of docked window) (when used with _ChildWindows or _RootWindow)
	RootAndChildWindows           = nil,
}


--#endregion

--#region ImGui Types

---@class ImVec2
---@field x number
---@field y number
ImVec2 = {}

---@return ImVec2
function ImVec2:new() end

---@param x number
---@param y number
---@return ImVec2
function ImVec2:new(x,y) end

---@class ImVec4
---@field x number
---@field y number
---@field z number
---@field w number
ImVec4 = {}

---@return ImVec4
function ImVec4:new() end

---@param x number
---@param y number
---@param z number
---@param w number
---@return ImVec4
function ImVec4:new(x,y,z,w) end

---@class ImGuiStyle
---@field Alpha float  Global alpha applies to everything in Dear ImGui.
---@field DisabledAlpha float  Additional alpha multiplier applied by BeginDisabled(). Multiply over current value of Alpha.
---@field WindowPadding ImVec2  Padding within a window.
---@field WindowRounding float  Radius of window corners rounding. Set to 0.0f to have rectangular windows. Large values tend to lead to variety of artifacts and are not recommended.
---@field WindowBorderSize float  Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
---@field WindowBorderHoverPadding float  Hit-testing extent outside/inside resizing border. Also extend determination of hovered window. Generally meaningfully larger than WindowBorderSize to make it easy to reach borders.
---@field WindowMinSize ImVec2  Minimum window size. This is a global setting. If you want to constrain individual windows, use SetNextWindowSizeConstraints().
---@field WindowTitleAlign ImVec2  Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
---@field WindowMenuButtonPosition ImGuiDir  Side of the collapsing/docking button in the title bar (None/Left/Right). Defaults to ImGuiDir_Left.
---@field ChildRounding float  Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
---@field ChildBorderSize float  Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
---@field PopupRounding float  Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
---@field PopupBorderSize float  Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
---@field FramePadding ImVec2  Padding within a framed rectangle (used by most widgets).
---@field FrameRounding float  Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
---@field FrameBorderSize float  Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
---@field ItemSpacing ImVec2  Horizontal and vertical spacing between widgets/lines.
---@field ItemInnerSpacing ImVec2  Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
---@field CellPadding ImVec2  Padding within a table cell. Cellpadding.x is locked for entire table. CellPadding.y may be altered between different rows.
---@field TouchExtraPadding ImVec2  Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
---@field IndentSpacing float  Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
---@field ColumnsMinSpacing float  Minimum horizontal spacing between two columns. Preferably > (FramePadding.x + 1).
---@field ScrollbarSize float  Width of the vertical scrollbar, Height of the horizontal scrollbar.
---@field ScrollbarRounding float  Radius of grab corners for scrollbar.
---@field GrabMinSize float  Minimum width/height of a grab box for slider/scrollbar.
---@field GrabRounding float  Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
---@field LogSliderDeadzone float  The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
---@field ImageBorderSize float  Thickness of border around Image() calls.
---@field TabRounding float  Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
---@field TabBorderSize float  Thickness of border around tabs.
---@field TabCloseButtonMinWidthSelected float  -1: always visible. 0.0f: visible when hovered. >0.0f: visible when hovered if minimum width.
---@field TabCloseButtonMinWidthUnselected float  -1: always visible. 0.0f: visible when hovered. >0.0f: visible when hovered if minimum width. FLT_MAX: never show close button when unselected.
---@field TabBarBorderSize float  Thickness of tab-bar separator, which takes on the tab active color to denote focus.
---@field TabBarOverlineSize float  Thickness of tab-bar overline, which highlights the selected tab-bar.
---@field TableAngledHeadersAngle float  Angle of angled headers (supported values range from -50.0f degrees to +50.0f degrees).
---@field TableAngledHeadersTextAlign ImVec2 lignment of angled headers within the cell
---@field TreeLinesFlags ImGuiTreeNodeFlags  Default way to draw lines connecting TreeNode hierarchy. ImGuiTreeNodeFlags_DrawLinesNone or ImGuiTreeNodeFlags_DrawLinesFull or ImGuiTreeNodeFlags_DrawLinesToNodes.
---@field TreeLinesSize float  Thickness of outlines when using ImGuiTreeNodeFlags_DrawLines.
---@field TreeLinesRounding float  Radius of lines connecting child nodes to the vertical line.
---@field ColorButtonPosition ImGuiDir  Side of the color button in the ColorEdit4 widget (left/right). Defaults to ImGuiDir_Right.
---@field ButtonTextAlign ImVec2  Alignment of button text when button is larger than text. Defaults to (0.5f, 0.5f) (centered).
---@field SelectableTextAlign ImVec2  Alignment of selectable text. Defaults to (0.0f, 0.0f) (top-left aligned). It's generally important to keep this left-aligned if you want to lay multiple items on a same line.
---@field SeparatorTextBorderSize float  Thickness of border in SeparatorText()
---@field SeparatorTextAlign ImVec2  Alignment of text within the separator. Defaults to (0.0f, 0.5f) (left aligned, center).
---@field SeparatorTextPadding ImVec2  Horizontal offset of text from each edge of the separator + spacing on other axis. Generally small values. .y is recommended to be == FramePadding.y.
---@field DisplayWindowPadding ImVec2  Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen.
---@field DisplaySafeAreaPadding ImVec2  Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents. Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured).
---@field DockingSeparatorSize float  Thickness of resizing border between docked windows
---@field MouseCursorScale float  Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). We apply per-monitor DPI scaling over this scale. May be removed later.
---@field AntiAliasedLines boolean  Enable anti-aliased lines/borders. Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
---@field AntiAliasedLinesUseTex boolean  Enable anti-aliased lines/borders using textures where possible. Require backend to render with bilinear filtering (NOT point/nearest filtering). Latched at the beginning of the frame (copied to ImDrawList).
---@field AntiAliasedFill boolean  Enable anti-aliased edges around filled shapes (rounded rectangles, circles, etc.). Disable if you are really tight on CPU/GPU. Latched at the beginning of the frame (copied to ImDrawList).
---@field CurveTessellationTol float  Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
---@field CircleTessellationMaxError float  Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.
---@field Colors table<ImGuiCol, ImVec4>  Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled() or drawing rounded corner rectangles with no explicit segment count specified. Decrease for higher quality but more geometry.

---@class ImFontAtlas
--TODO

---@class ImFont
ImFont = {}

function ImFont.IsGlyphInFont(c) end
function ImFont.IsLoaded() end
function ImFont.GetDebugName() end

---@class ImGuiKeyData
---@field Down boolean True for if key is down
---@field DownDuration number Duration the key has been down (<0.0f: not pressed, 0.0f: just pressed, >0.0f: time held)
---@field DownDurationPrev number Last frame duration the key has been down
---@field AnalogValue number 0.0f..1.0f for gamepad values

---@class ImGuiIO
---@field ConfigFlags ImGuiConfigFlags|integer;             // = 0              // See ImGuiConfigFlags_ enum. Set by user/application. Keyboard/Gamepad navigation options, etc.
---@field BackendFlags ImGuiBackendFlags|integer   See ImGuiBackendFlags_ enum. Set by backend (imgui_impl_xxx files or custom backend) to communicate features supported by the backend.
---@field DisplaySize ImVec2       Main display size, in pixels (== GetMainViewport()->Size). May change every frame.
---@field DisplayFramebufferScale ImVec2       Main display density. For retina display where window coordinates are different from framebuffer coordinates. This will affect font density + will end up in ImDrawData::FramebufferScale.
---@field DeltaTime number        Time elapsed since last frame, in seconds. May change every frame.
---@field IniSavingRate number        Minimum time between saving positions/sizes to .ini file, in seconds.
---@field IniFilename string  Path to .ini file (important: default "imgui.ini" is relative to current working dir!). Set NULL to disable automatic .ini loading/saving or if you want to manually call LoadIniSettingsXXX() / SaveIniSettingsXXX() functions.
---@field LogFilename string  Path to .log file (default parameter to ImGui::LogToFile when no file is specified).
---@field UserData any        Store your own data.
---@field Fonts ImFontAtlas Font atlas: load, rasterize and pack one or more fonts into a single texture.
---@field FontDefault ImFont      Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
---@field FontAllowUserScaling boolean        [OBSOLETE] Allow user scaling text of individual window with CTRL+Wheel.
---@field ConfigNavSwapGamepadButtons boolean        Swap Activate<>Cancel (A<>B) buttons, matching typical "Nintendo/Japanese style" gamepad layout.
---@field ConfigNavMoveSetMousePos boolean        Directional/tabbing navigation teleports the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is difficult. Will update io.MousePos and set io.WantSetMousePos=true.
---@field ConfigNavCaptureKeyboard boolean        Sets io.WantCaptureKeyboard when io.NavActive is set.
---@field ConfigNavEscapeClearFocusItem boolean        Pressing Escape can clear focused item + navigation id/highlight. Set to false if you want to always keep highlight on.
---@field ConfigNavEscapeClearFocusWindow boolean        Pressing Escape can clear focused window as well (super set of io.ConfigNavEscapeClearFocusItem).
---@field ConfigNavCursorVisibleAuto boolean        Using directional navigation key makes the cursor visible. Mouse click hides the cursor.
---@field ConfigNavCursorVisibleAlways boolean        Navigation cursor is always visible.
---@field ConfigDockingNoSplit boolean        Simplified docking mode: disable window splitting, so docking is limited to merging multiple windows together into tab-bars.
---@field ConfigDockingWithShift boolean        Enable docking with holding Shift key (reduce visual noise, allows dropping in wider space)
---@field ConfigDockingAlwaysTabBar boolean        [BETA] [FIXME: This currently creates regression with auto-sizing and general overhead] Make every single floating window display within a docking node.
---@field ConfigDockingTransparentPayload boolean        [BETA] Make window or viewport transparent when docking and only display docking boxes on the target viewport. Useful if rendering of multiple viewport cannot be synced. Best used with ConfigViewportsNoAutoMerge.
---@field ConfigViewportsNoAutoMerge boolean        Set to make all floating imgui windows always create their own viewport. Otherwise, they are merged into the main host viewports when overlapping it. May also set ImGuiViewportFlags_NoAutoMerge on individual viewport.
---@field ConfigViewportsNoTaskBarIcon boolean        Disable default OS task bar icon flag for secondary viewports. When a viewport doesn't want a task bar icon, ImGuiViewportFlags_NoTaskBarIcon will be set on it.
---@field ConfigViewportsNoDecoration boolean        Disable default OS window decoration flag for secondary viewports. When a viewport doesn't want window decorations, ImGuiViewportFlags_NoDecoration will be set on it. Enabling decoration can create subsequent issues at OS levels (e.g. minimum window size).
---@field ConfigViewportsNoDefaultParent boolean        Disable default OS parenting to main viewport for secondary viewports. By default, viewports are marked with ParentViewportId = <main_viewport>, expecting the platform backend to setup a parent/child relationship between the OS windows (some backend may ignore this). Set to true if you want the default to be 0, then all viewports will be top-level OS windows.
---@field ConfigDpiScaleFonts boolean        [EXPERIMENTAL] Automatically overwrite style.FontScaleDpi when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
---@field ConfigDpiScaleViewports boolean        [EXPERIMENTAL] Scale Dear ImGui and Platform Windows when Monitor DPI changes.
---@field MouseDrawCursor boolean        Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor). Cannot be easily renamed to 'io.ConfigXXX' because this is frequently used by backend implementations.
---@field ConfigMacOSXBehaviors boolean        Swap Cmd<>Ctrl keys + OS X style text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl.
---@field ConfigInputTrickleEventQueue boolean        Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates.
---@field ConfigInputTextCursorBlink boolean        Enable blinking cursor (optional as some users consider it to be distracting).
---@field ConfigInputTextEnterKeepActive boolean        [BETA] Pressing Enter will keep item active and select contents (single-line only).
---@field ConfigDragClickToInputText boolean        [BETA] Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving). Not desirable on devices without a keyboard.
---@field ConfigWindowsResizeFromEdges boolean        Enable resizing of windows from their edges and from the lower-left corner. This requires ImGuiBackendFlags_HasMouseCursors for better mouse cursor feedback. (This used to be a per-window ImGuiWindowFlags_ResizeFromAnySide flag)
---@field ConfigWindowsMoveFromTitleBarOnly boolean        Enable allowing to move windows only when clicking on their title bar. Does not apply to windows without a title bar.
---@field ConfigWindowsCopyContentsWithCtrlC boolean        [EXPERIMENTAL] CTRL+C copy the contents of focused window into the clipboard. Experimental because: (1) has known issues with nested Begin/End pairs (2) text output quality varies (3) text output is in submission order rather than spatial order.
---@field ConfigScrollbarScrollByPage boolean        Enable scrolling page by page when clicking outside the scrollbar grab. When disabled, always scroll to clicked location. When enabled, Shift+Click scrolls to clicked location.
---@field ConfigMemoryCompactTimer number        Timer (in seconds) to free transient windows/tables memory buffers when unused. Set to -1.0f to disable.
---@field MouseDoubleClickTime number        Time for a double-click, in seconds.
---@field MouseDoubleClickMaxDist number        Distance threshold to stay in to validate a double-click, in pixels.
---@field MouseDragThreshold number        Distance threshold before considering we are dragging.
---@field KeyRepeatDelay number        When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
---@field KeyRepeatRate number        When holding a key/button, rate at which it repeats, in seconds.
---@field ConfigErrorRecovery boolean        Enable error recovery support. Some errors won't be detected and lead to direct crashes if recovery is disabled.
---@field ConfigErrorRecoveryEnableAssert boolean        Enable asserts on recoverable error. By default call IM_ASSERT() when returning from a failing IM_ASSERT_USER_ERROR()
---@field ConfigErrorRecoveryEnableDebugLog boolean        Enable debug log output on recoverable errors.
---@field ConfigErrorRecoveryEnableTooltip boolean        Enable tooltip on recoverable errors. The tooltip include a way to enable asserts if they were disabled.
---@field ConfigDebugIsDebuggerPresent boolean        Enable various tools calling IM_DEBUG_BREAK().
---@field ConfigDebugHighlightIdConflicts boolean        Highlight and show an error message popup when multiple items have conflicting identifiers.
---@field ConfigDebugHighlightIdConflictsShowItemPicker boolean        Show "Item Picker" button in aforementioned popup.
---@field ConfigDebugBeginReturnValueOnce boolean        First-time calls to Begin()/BeginChild() will return false. NEEDS TO BE SET AT APPLICATION BOOT TIME if you don't want to miss windows.
---@field ConfigDebugBeginReturnValueLoop boolean        Some calls to Begin()/BeginChild() will return false. Will cycle through window depths then repeat. Suggested use: add "io.ConfigDebugBeginReturnValue = io.KeyShift" in your main loop then occasionally press SHIFT. Windows should be flickering while running.
---@field ConfigDebugIgnoreFocusLoss boolean        Ignore io.AddFocusEvent(false), consequently not calling io.ClearInputKeys()/io.ClearInputMouse() in input processing.
---@field ConfigDebugIniSettings boolean        Save .ini data with extra comments (particularly helpful for Docking, but makes saving slower)
---@field BackendPlatformName string
---@field BackendRendererName string
---@field BackendPlatformUserData any        User data for platform backend
---@field BackendRendererUserData any        User data for renderer backend
---@field BackendLanguageUserData any        User data for non C++ programming language backend
---@field WantCaptureMouse boolean        Set when Dear ImGui will use mouse inputs, in this case do not dispatch them to your main game/application (either way, always pass on mouse inputs to imgui). (e.g. unclicked mouse is hovering over an imgui window, widget is active, mouse was clicked over an imgui window, etc.).
---@field WantCaptureKeyboard boolean        Set when Dear ImGui will use keyboard inputs, in this case do not dispatch them to your main game/application (either way, always pass keyboard inputs to imgui). (e.g. InputText active, or an imgui window is focused and navigation is enabled, etc.).
---@field WantTextInput boolean        Mobile/console: when set, you may display an on-screen keyboard. This is set by Dear ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
---@field WantSetMousePos boolean        MousePos has been altered, backend should reposition mouse on next frame. Rarely used! Set only when io.ConfigNavMoveSetMousePos is enabled.
---@field WantSaveIniSettings boolean        When manual .ini load/save is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. Important: clear io.WantSaveIniSettings yourself after saving!
---@field NavActive boolean        Keyboard/Gamepad navigation is currently allowed (will handle ImGuiKey_NavXXX events) = a window is focused and it doesn't use the ImGuiWindowFlags_NoNavInputs flag.
---@field NavVisible boolean        Keyboard/Gamepad navigation highlight is visible and allowed (will handle ImGuiKey_NavXXX events).
---@field Framerate number        Estimate of application framerate (rolling average over 60 frames, based on io.DeltaTime), in frame per second. Solely for convenience. Slow applications may not want to use a moving average or may want to reset underlying buffers occasionally.
---@field MetricsRenderVertices integer         Vertices output during last call to Render()
---@field MetricsRenderIndices integer         Indices output during last call to Render() = number of triangles * 3
---@field MetricsRenderWindows integer         Number of visible windows
---@field MetricsActiveWindows integer         Number of active windows
---@field MouseDelta ImVec2       Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.
---@field MousePos ImVec2       Mouse position, in pixels. Set to ImVec2(-FLT_MAX, -FLT_MAX) if mouse is unavailable (on another screen, etc.)
---@field MouseDown table<integer, boolean>; Mouse buttons: 0=left, 1=right, 2=middle + extras (ImGuiMouseButton_COUNT == 5). Dear ImGui mostly uses left and right buttons. Other buttons allow us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
---@field MouseWheel number        Mouse wheel Vertical: 1 unit scrolls about 5 lines text. >0 scrolls Up, <0 scrolls Down. Hold SHIFT to turn vertical scroll into horizontal scroll.
---@field MouseWheelH number        Mouse wheel Horizontal. >0 scrolls Left, <0 scrolls Right. Most users don't have a mouse with a horizontal wheel, may not be filled by all backends.
---@field MouseSource ImGuiMouseSource|integer  Mouse actual input peripheral (Mouse/TouchScreen/Pen).
---@field MouseHoveredViewport integer      (Optional) Modify using io.AddMouseViewportEvent(). With multi-viewports: viewport the OS mouse is hovering. If possible _IGNORING_ viewports with the ImGuiViewportFlags_NoInputs flag is much better (few backends can handle that). Set io.BackendFlags |= ImGuiBackendFlags_HasMouseHoveredViewport if you can provide this info. If you don't imgui will infer the value using the rectangles and last focused time of the viewports it knows about (ignoring other OS windows).
---@field KeyCtrl boolean        Keyboard modifier down: Control
---@field KeyShift boolean        Keyboard modifier down: Shift
---@field KeyAlt boolean        Keyboard modifier down: Alt
---@field KeySuper boolean        Keyboard modifier down: Cmd/Super/Windows
---@field KeyMods integer  Key mods flags (any of ImGuiMod_Ctrl/ImGuiMod_Shift/ImGuiMod_Alt/ImGuiMod_Super flags, same as io.KeyCtrl/KeyShift/KeyAlt/KeySuper but merged into flags. Read-only, updated by NewFrame()
---@field KeysData table<integer,ImGuiKeyData> Key state for all known keys. MUST use 'key - ImGuiKey_NamedKey_BEGIN' as index. Use IsKeyXXX() functions to access this.
---@field WantCaptureMouseUnlessPopupClose boolean        Alternative to WantCaptureMouse: (WantCaptureMouse == true && WantCaptureMouseUnlessPopupClose == false) when a click over void is expected to close a popup.
---@field MousePosPrev ImVec2       Previous mouse position (note that MouseDelta is not necessary == MousePos-MousePosPrev, in case either position is invalid)
---@field MouseClickedPos table<integer,ImVec2> Position at time of clicking
---@field MouseClickedTime table<integer,number> Time of last click (used to figure out double-click)
---@field MouseClicked table<integer,boolean> Mouse button went from !Down to Down (same as MouseClickedCount[x] != 0)
---@field MouseDoubleClicked table<integer,boolean> Has mouse button been double-clicked? (same as MouseClickedCount[x] == 2)
---@field MouseClickedCount table<integer,integer> == 0 (not clicked), == 1 (same as MouseClicked[]), == 2 (double-clicked), == 3 (triple-clicked) etc. when going from !Down to Down
---@field MouseClickedLastCount table<integer,integer> Count successive number of clicks. Stays valid after mouse release. Reset after another click is done.
---@field MouseReleased table<integer,boolean> Mouse button went from Down to !Down
---@field MouseReleasedTime table<integer,number> Time of last released (rarely used! but useful to handle delayed single-click when trying to disambiguate them from double-click).
---@field MouseDownOwned table<integer,boolean> Track if button was clicked inside a dear imgui window or over void blocked by a popup. We don't request mouse capture from the application if click started outside ImGui bounds.
---@field MouseDownOwnedUnlessPopupClose table<integer,boolean> Track if button was clicked inside a dear imgui window.
---@field MouseWheelRequestAxisSwap boolean        On a non-Mac system, holding SHIFT requests WheelY to perform the equivalent of a WheelX event. On a Mac system this is already enforced by the system.
---@field MouseCtrlLeftAsRightClick boolean        (OSX) Set to true when the current click was a Ctrl+click that spawned a simulated right click
---@field MouseDownDuration table<integer, float> Duration the mouse button has been down (0.0f == just clicked)
---@field MouseDownDurationPrev table<integer, float> Previous time the mouse button has been down
---@field MouseDragMaxDistanceAbs table<integer, ImVec2> Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
---@field MouseDragMaxDistanceSqr table<integer, float> Squared maximum distance of how much mouse has traveled from the clicking point (used for moving thresholds)
---@field PenPressure number        Touch/Pen pressure (0.0f to 1.0f, should be >0.0f only when MouseDown[0] == true). Helper storage currently unused by Dear ImGui.
---@field AppFocusLost boolean        Only modify via AddFocusEvent()
---@field AppAcceptingEvents boolean        Only modify via SetAppAcceptingEvents()
---@field InputQueueSurrogate integer    For AddInputCharacterUTF16()


---@class ImGuiInputTextCallbackData
---@field EventFlag number One ImGuiInputTextFlags_Callback*    // Read-only
---@field Flags number What user passed to InputText()      // Read-only
---@field UserData any What user passed to InputText()      // Read-only
---@field EventChar any Character input                      // Read-write   // [CharFilter] Replace character with another one, or set to zero to drop. return 1 is equivalent to setting EventChar=0;
---@field EventKey integer Key pressed (Up/Down/TAB)            // Read-only    // [Completion,History]
---@field Buf string Text buffer                          // Read-write   // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
---@field BufTextLen integer Text length (in bytes)               // Read-write   // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
---@field BufSize integer Buffer size (in bytes) = capacity+1  // Read-only    // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
---@field BufDirty boolean Set if you modify Buf/BufTextLen!    // Write        // [Completion,History,Always]
---@field CursorPos integer // Read-write   // [Completion,History,Always]
---@field SelectionStart integer // Read-write   // [Completion,History,Always] == to SelectionEnd when no selection)
---@field SelectionEnd integer // Read-write   // [Completion,History,Always]
local ImGuiInputTextCallbackData = {}

---@param pos integer
---@param bytes_count integer
function ImGuiInputTextCallbackData:DeleteChars(pos, bytes_count) end

---@param pos integer
---@param text string
function ImGuiInputTextCallbackData:InsertChars(pos, text) end

function ImGuiInputTextCallbackData:SelectAll() end
function ImGuiInputTextCallbackData:ClearSelection() end

---@return boolean
function ImGuiInputTextCallbackData:HasSelection() end

--#endregion

--#region ImGui Bindings
ImGui = {}

function ImGui.ShowDemoWindow() end

---@param open boolean
---@return boolean open
function ImGui.ShowDemoWindow(open) end

---@param name string
---@return boolean
function ImGui.Begin(name) end

---@param name string
---@param flags integer
---@return boolean
function ImGui.Begin(name, flags) end

---@param name string
---@param open boolean
---@return boolean open
---@return boolean
function ImGui.Begin(name, open) end

---@param name string
---@param open boolean
---@param flags integer
---@return boolean open
---@return boolean
function ImGui.Begin(name, open, flags) end

function ImGui.End() end

---@param name string
---@return boolean
function ImGui.BeginChild(name) end

---@param name string
---@param sizeX number
---@return boolean
function ImGui.BeginChild(name, sizeX) end

---@param name string
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.BeginChild(name, sizeX, sizeY) end

---@param name string
---@param sizeX number
---@param sizeY number
---@param child_flags integer
---@return boolean
function ImGui.BeginChild(name, sizeX, sizeY, child_flags) end

---@param name string
---@param sizeX number
---@param sizeY number
---@param child_flags integer
---@param window_flags integer
---@return boolean
function ImGui.BeginChild(name, sizeX, sizeY, child_flags, window_flags) end

function ImGui.EndChild() end

---@return boolean
function ImGui.IsWindowAppearing() end

---@return boolean
function ImGui.IsWindowCollapsed() end

---@return boolean
function ImGui.IsWindowFocused() end

---@param flags integer
---@return boolean
function ImGui.IsWindowFocused(flags) end

---@return boolean
function ImGui.IsWindowHovered() end

---@param flags integer
---@return boolean
function ImGui.IsWindowHovered(flags) end

---@return ImDrawList
function ImGui.GetWindowDrawList() end

---@return number
---@return number
function ImGui.GetWindowPos() end

---@return number
---@return number
function ImGui.GetWindowSize() end

---@return number
function ImGui.GetWindowWidth() end

---@return number
function ImGui.GetWindowHeight() end

---@param posX number
---@param posY number
function ImGui.SetNextWindowPos(posX, posY) end

---@param posX number
---@param posY number
---@param cond integer
function ImGui.SetNextWindowPos(posX, posY, cond) end

---@param posX number
---@param posY number
---@param cond integer
---@param pivotX number
---@param pivotY number
function ImGui.SetNextWindowPos(posX, posY, cond, pivotX, pivotY) end

---@param sizeX number
---@param sizeY number
function ImGui.SetNextWindowSize(sizeX, sizeY) end

---@param sizeX number
---@param sizeY number
---@param cond integer
function ImGui.SetNextWindowSize(sizeX, sizeY, cond) end

---@param minX number
---@param minY number
---@param maxX number
---@param maxY number
function ImGui.SetNextWindowSizeConstraints(minX, minY, maxX, maxY) end

---@param sizeX number
---@param sizeY number
function ImGui.SetNextWindowContentSize(sizeX, sizeY) end

---@param collapsed boolean
function ImGui.SetNextWindowCollapsed(collapsed) end

---@param collapsed boolean
---@param cond integer
function ImGui.SetNextWindowCollapsed(collapsed, cond) end

function ImGui.SetNextWindowFocus() end

---@param alpha number
function ImGui.SetNextWindowBgAlpha(alpha) end

---@param posX number
---@param posY number
function ImGui.SetWindowPos(posX, posY) end

---@param posX number
---@param posY number
---@param cond integer
function ImGui.SetWindowPos(posX, posY, cond) end

---@param sizeX number
---@param sizeY number
function ImGui.SetWindowSize(sizeX, sizeY) end

---@param sizeX number
---@param sizeY number
---@param cond integer
function ImGui.SetWindowSize(sizeX, sizeY, cond) end

---@param collapsed boolean
function ImGui.SetWindowCollapsed(collapsed) end

---@param collapsed boolean
---@param cond integer
function ImGui.SetWindowCollapsed(collapsed, cond) end

function ImGui.SetWindowFocus() end

---@param scale number
function ImGui.SetWindowFontScale(scale) end

---@param name string
---@param posX number
---@param posY number
function ImGui.SetWindowPos(name, posX, posY) end

---@param name string
---@param posX number
---@param posY number
---@param cond integer
function ImGui.SetWindowPos(name, posX, posY, cond) end

---@param name string
---@param sizeX number
---@param sizeY number
function ImGui.SetWindowSize(name, sizeX, sizeY) end

---@param name string
---@param sizeX number
---@param sizeY number
---@param cond integer
function ImGui.SetWindowSize(name, sizeX, sizeY, cond) end

---@param name string
---@param collapsed boolean
function ImGui.SetWindowCollapsed(name, collapsed) end

---@param name string
---@param collapsed boolean
---@param cond integer
function ImGui.SetWindowCollapsed(name, collapsed, cond) end

---@param name string
function ImGui.SetWindowFocus(name) end

---@return number
---@return number
function ImGui.GetContentRegionMax() end

---@return number
---@return number
function ImGui.GetContentRegionAvail() end

---@return number
function ImGui.GetScrollX() end

---@return number
function ImGui.GetScrollY() end

---@return number
function ImGui.GetScrollMaxX() end

---@return number
function ImGui.GetScrollMaxY() end

---@param scrollX number
function ImGui.SetScrollX(scrollX) end

---@param scrollY number
function ImGui.SetScrollY(scrollY) end

function ImGui.SetScrollHereX() end

---@param centerXRatio number
function ImGui.SetScrollHereX(centerXRatio) end

function ImGui.SetScrollHereY() end

---@param centerYRatio number
function ImGui.SetScrollHereY(centerYRatio) end

---@param localX number
function ImGui.SetScrollFromPosX(localX) end

---@param localX number
---@param centerXRatio number
function ImGui.SetScrollFromPosX(localX, centerXRatio) end

---@param localY number
function ImGui.SetScrollFromPosY(localY) end

---@param localY number
---@param centerYRatio number
function ImGui.SetScrollFromPosY(localY, centerYRatio) end

---@param idx integer
---@param col integer
function ImGui.PushStyleColor(idx, col) end

---@param idx integer
---@param colR number
---@param colG number
---@param colB number
---@param colA number
function ImGui.PushStyleColor(idx, colR, colG, colB, colA) end

function ImGui.PopStyleColor() end

---@param count integer
function ImGui.PopStyleColor(count) end

---@param idx integer
---@param val number
function ImGui.PushStyleVar(idx, val) end

---@param idx integer
---@param valX number
---@param valY number
function ImGui.PushStyleVar(idx, valX, valY) end

function ImGui.PopStyleVar() end

---@param count integer
function ImGui.PopStyleVar(count) end

---@param idx integer
---@return number
---@return number
---@return number
---@return number
function ImGui.GetStyleColorVec4(idx) end

---@return number
function ImGui.GetFontSize() end

---@return number
---@return number
function ImGui.GetFontTexUvWhitePixel() end

---@param idx integer
---@param alphaMul number
---@return integer
function ImGui.GetColorU32(idx, alphaMul) end

---@param colR number
---@param colG number
---@param colB number
---@param colA number
---@return integer
function ImGui.GetColorU32(colR, colG, colB, colA) end

---@param col integer
---@return integer
function ImGui.GetColorU32(col) end

---@param itemWidth number
function ImGui.PushItemWidth(itemWidth) end

function ImGui.PopItemWidth() end

---@param itemWidth number
function ImGui.SetNextItemWidth(itemWidth) end

---@return number
function ImGui.CalcItemWidth() end

function ImGui.PushTextWrapPos() end

---@param wrapLocalPosX number
function ImGui.PushTextWrapPos(wrapLocalPosX) end

function ImGui.PopTextWrapPos() end

---@param allowKeyboardFocus boolean
function ImGui.PushAllowKeyboardFocus(allowKeyboardFocus) end

function ImGui.PopAllowKeyboardFocus() end

---@param _repeat boolean
function ImGui.PushButtonRepeat(_repeat) end

function ImGui.PopButtonRepeat() end

function ImGui.Separator() end

---@param label string
function ImGui.SeparatorText(label) end

function ImGui.SameLine() end

---@param offsetFromStartX number
function ImGui.SameLine(offsetFromStartX) end

---@param offsetFromStartX number
---@param spacing number
function ImGui.SameLine(offsetFromStartX, spacing) end

function ImGui.NewLine() end

function ImGui.Spacing() end

---@param sizeX number
---@param sizeY number
function ImGui.Dummy(sizeX, sizeY) end

function ImGui.Indent() end

---@param indentW number
function ImGui.Indent(indentW) end

function ImGui.Unindent() end

---@param indentW number
function ImGui.Unindent(indentW) end

function ImGui.BeginGroup() end

function ImGui.EndGroup() end

---@return number
---@return number
function ImGui.GetCursorPos() end

---@return number
function ImGui.GetCursorPosX() end

---@return number
function ImGui.GetCursorPosY() end

---@param localX number
---@param localY number
function ImGui.SetCursorPos(localX, localY) end

---@param localX number
function ImGui.SetCursorPosX(localX) end

---@param localY number
function ImGui.SetCursorPosY(localY) end

---@return number
---@return number
function ImGui.GetCursorStartPos() end

---@return number
---@return number
function ImGui.GetCursorScreenPos() end

---@param posX number
---@param posY number
function ImGui.SetCursorScreenPos(posX, posY) end

function ImGui.AlignTextToFramePadding() end

---@return number
function ImGui.GetTextLineHeight() end

---@return number
function ImGui.GetTextLineHeightWithSpacing() end

---@return number
function ImGui.GetFrameHeight() end

---@return number
function ImGui.GetFrameHeightWithSpacing() end

---@param stringID string
function ImGui.PushID(stringID) end

---@param intID integer
function ImGui.PushID(intID) end

function ImGui.PopID() end

---@param stringID string
---@return integer
function ImGui.GetID(stringID) end

---@param text string
function ImGui.TextUnformatted(text) end

---@param text string
function ImGui.Text(text) end

---@param colR number
---@param colG number
---@param colB number
---@param colA number
---@param text string
function ImGui.TextColored(colR, colG, colB, colA, text) end

---@param text string
function ImGui.TextDisabled(text) end

---@param text string
function ImGui.TextWrapped(text) end

---@param label string
---@param text string
function ImGui.LabelText(label, text) end

---@param text string
function ImGui.BulletText(text) end

---@param label string
---@return boolean
function ImGui.Button(label) end

---@param label string
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.Button(label, sizeX, sizeY) end

---@param label string
---@return boolean
function ImGui.SmallButton(label) end

---@param stringID string
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.InvisibleButton(stringID, sizeX, sizeY) end

---@param stringID string
---@param dir integer
---@return boolean
function ImGui.ArrowButton(stringID, dir) end

function ImGui.Image() end

function ImGui.ImageButton() end

---@param label string
---@param v boolean
---@return boolean v
---@return boolean pressed
function ImGui.Checkbox(label, v) end

---@return boolean
function ImGui.CheckboxFlags() end

---@param label string
---@param active boolean
---@return boolean
function ImGui.RadioButton(label, active) end

---@param label string
---@param v integer
---@param vButton integer
---@return integer
---@return boolean
function ImGui.RadioButton(label, v, vButton) end

---@param fraction number
function ImGui.ProgressBar(fraction) end

---@param fraction number
---@param sizeX number
---@param sizeY number
function ImGui.ProgressBar(fraction, sizeX, sizeY) end

---@param fraction number
---@param sizeX number
---@param sizeY number
---@param overlay string
function ImGui.ProgressBar(fraction, sizeX, sizeY, overlay) end

function ImGui.Bullet() end

---@param label string
---@param previewValue string
---@return boolean
function ImGui.BeginCombo(label, previewValue) end

---@param label string
---@param previewValue string
---@param flags integer
---@return boolean
function ImGui.BeginCombo(label, previewValue, flags) end

function ImGui.EndCombo() end

---@param label string
---@param currentItem integer
---@param items table
---@param itemsCount integer
---@return integer
---@return boolean
function ImGui.Combo(label, currentItem, items, itemsCount) end

---@param label string
---@param currentItem integer
---@param items table
---@param itemsCount integer
---@param popupMaxHeightInItems integer
---@return integer
---@return boolean
function ImGui.Combo(label, currentItem, items, itemsCount, popupMaxHeightInItems) end

---@param label string
---@param currentItem integer
---@param itemsSeparatedByZeros string
---@return integer
---@return boolean
function ImGui.Combo(label, currentItem, itemsSeparatedByZeros) end

---@param label string
---@param currentItem integer
---@param itemsSeparatedByZeros string
---@param popupMaxHeightInItems integer
---@return integer
---@return boolean
function ImGui.Combo(label, currentItem, itemsSeparatedByZeros, popupMaxHeightInItems) end

---@param label string
---@param v number
---@return number
---@return boolean
function ImGui.DragFloat(label, v) end

---@param label string
---@param v number
---@param v_speed number
---@return number
---@return boolean
function ImGui.DragFloat(label, v, v_speed) end

---@param label string
---@param v number
---@param v_speed number
---@param v_min number
---@return number
---@return boolean
function ImGui.DragFloat(label, v, v_speed, v_min) end

---@param label string
---@param v number
---@param v_speed number
---@param v_min number
---@param v_max number
---@return number
---@return boolean
function ImGui.DragFloat(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v number
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@return number
---@return boolean
function ImGui.DragFloat(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v number
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.DragFloat(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragFloat2(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragFloat2(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@return table
---@return boolean
function ImGui.DragFloat2(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.DragFloat2(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.DragFloat2(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragFloat2(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragFloat3(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragFloat3(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@return table
---@return boolean
function ImGui.DragFloat3(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.DragFloat3(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.DragFloat3(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragFloat3(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragFloat4(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragFloat4(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@return table
---@return boolean
function ImGui.DragFloat4(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.DragFloat4(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.DragFloat4(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragFloat4(label, v, v_speed, v_min, v_max, format, flags) end

function ImGui.DragFloatRange2() end

---@param label string
---@param v integer
---@return integer
---@return boolean
function ImGui.DragInt(label, v) end

---@param label string
---@param v integer
---@param v_speed number
---@return integer
---@return boolean
function ImGui.DragInt(label, v, v_speed) end

---@param label string
---@param v integer
---@param v_speed number
---@param v_min integer
---@return integer
---@return boolean
function ImGui.DragInt(label, v, v_speed, v_min) end

---@param label string
---@param v integer
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@return integer
---@return boolean
function ImGui.DragInt(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v integer
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@return integer
---@return boolean
function ImGui.DragInt(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v integer
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return integer
---@return boolean
function ImGui.DragInt(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragInt2(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragInt2(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@return table
---@return boolean
function ImGui.DragInt2(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.DragInt2(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.DragInt2(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragInt2(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragInt3(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragInt3(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@return table
---@return boolean
function ImGui.DragInt3(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.DragInt3(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.DragInt3(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragInt3(label, v, v_speed, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.DragInt4(label, v) end

---@param label string
---@param v table
---@param v_speed number
---@return table
---@return boolean
function ImGui.DragInt4(label, v, v_speed) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@return table
---@return boolean
function ImGui.DragInt4(label, v, v_speed, v_min) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.DragInt4(label, v, v_speed, v_min, v_max) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.DragInt4(label, v, v_speed, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_speed number
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.DragInt4(label, v, v_speed, v_min, v_max, format, flags) end

function ImGui.DragIntRange2() end

function ImGui.DragScalar() end

function ImGui.DragScalarN() end

---@param label string
---@param v number
---@param v_min number
---@param v_max number
---@return number
---@return boolean
function ImGui.SliderFloat(label, v, v_min, v_max) end

---@param label string
---@param v number
---@param v_min number
---@param v_max number
---@param format string
---@return number
---@return boolean
function ImGui.SliderFloat(label, v, v_min, v_max, format) end

---@param label string
---@param v number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.SliderFloat(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.SliderFloat2(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.SliderFloat2(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderFloat2(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.SliderFloat3(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.SliderFloat3(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderFloat3(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@return table
---@return boolean
function ImGui.SliderFloat4(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@return table
---@return boolean
function ImGui.SliderFloat4(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderFloat4(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v_rad number
---@return number
---@return boolean
function ImGui.SliderAngle(label, v_rad) end

---@param label string
---@param v_rad number
---@param v_degrees_min number
---@return number
---@return boolean
function ImGui.SliderAngle(label, v_rad, v_degrees_min) end

---@param label string
---@param v_rad number
---@param v_degrees_min number
---@param v_degrees_max number
---@return number
---@return boolean
function ImGui.SliderAngle(label, v_rad, v_degrees_min, v_degrees_max) end

---@param label string
---@param v_rad number
---@param v_degrees_min number
---@param v_degrees_max number
---@param format string
---@return number
---@return boolean
function ImGui.SliderAngle(label, v_rad, v_degrees_min, v_degrees_max, format) end

---@param label string
---@param v_rad number
---@param v_degrees_min number
---@param v_degrees_max number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.SliderAngle(label, v_rad, v_degrees_min, v_degrees_max, format, flags) end

---@param label string
---@param v integer
---@param v_min integer
---@param v_max integer
---@return integer
---@return boolean
function ImGui.SliderInt(label, v, v_min, v_max) end

---@param label string
---@param v integer
---@param v_min integer
---@param v_max integer
---@param format string
---@return integer
---@return boolean
function ImGui.SliderInt(label, v, v_min, v_max, format) end

---@param label string
---@param v integer
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return integer
---@return boolean
function ImGui.SliderInt(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.SliderInt2(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.SliderInt2(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderInt2(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.SliderInt3(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.SliderInt3(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderInt3(label, v, v_min, v_max, format, flags) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@return table
---@return boolean
function ImGui.SliderInt4(label, v, v_min, v_max) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@return table
---@return boolean
function ImGui.SliderInt4(label, v, v_min, v_max, format) end

---@param label string
---@param v table
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.SliderInt4(label, v, v_min, v_max, format, flags) end

function ImGui.SliderScalar() end

function ImGui.SliderScalarN() end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v number
---@param v_min number
---@param v_max number
---@return number
---@return boolean
function ImGui.VSliderFloat(label, sizeX, sizeY, v, v_min, v_max) end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v number
---@param v_min number
---@param v_max number
---@param format string
---@return number
---@return boolean
function ImGui.VSliderFloat(label, sizeX, sizeY, v, v_min, v_max, format) end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v number
---@param v_min number
---@param v_max number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.VSliderFloat(label, sizeX, sizeY, v, v_min, v_max, format, flags) end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v integer
---@param v_min integer
---@param v_max integer
---@return integer
---@return boolean
function ImGui.VSliderInt(label, sizeX, sizeY, v, v_min, v_max) end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v integer
---@param v_min integer
---@param v_max integer
---@param format string
---@return integer
---@return boolean
function ImGui.VSliderInt(label, sizeX, sizeY, v, v_min, v_max, format) end

---@param label string
---@param sizeX number
---@param sizeY number
---@param v integer
---@param v_min integer
---@param v_max integer
---@param format string
---@param flags integer
---@return integer
---@return boolean
function ImGui.VSliderInt(label, sizeX, sizeY, v, v_min, v_max, format, flags) end

function ImGui.VSliderScalar() end

---@param label string
---@param text string
---@param buf_size integer
---@return string
---@return boolean
function ImGui.InputText(label, text, buf_size) end

---@param label string
---@param text string
---@param buf_size integer
---@param flags integer
---@return string
---@return boolean
function ImGui.InputText(label, text, buf_size, flags) end

---@param label string
---@param text string
---@param buf_size integer
---@param flags integer
---@param callback fun(data: ImGuiInputTextCallbackData): number
---@return string
---@return boolean
function ImGui.InputText(label, text, buf_size, flags, callback) end

---@param label string
---@param text string
---@param buf_size integer
---@return string
---@return boolean
function ImGui.InputTextMultiline(label, text, buf_size) end

---@param label string
---@param text string
---@param buf_size integer
---@param sizeX number
---@param sizeY number
---@return string
---@return boolean
function ImGui.InputTextMultiline(label, text, buf_size, sizeX, sizeY) end

---@param label string
---@param text string
---@param buf_size integer
---@param sizeX number
---@param sizeY number
---@param flags integer
---@return string
---@return boolean
function ImGui.InputTextMultiline(label, text, buf_size, sizeX, sizeY, flags) end

---@param label string
---@param text string
---@param buf_size integer
---@param sizeX number
---@param sizeY number
---@param flags integer
---@param callback fun(data: ImGuiInputTextCallbackData): number
---@return string
---@return boolean
function ImGui.InputTextMultiline(label, text, buf_size, sizeX, sizeY, flags, callback) end

---@param label string
---@param hint string
---@param text string
---@param buf_size integer
---@return string
---@return boolean
function ImGui.InputTextWithHint(label, hint, text, buf_size) end

---@param label string
---@param hint string
---@param text string
---@param buf_size integer
---@param flags integer
---@return string
---@return boolean
function ImGui.InputTextWithHint(label, hint, text, buf_size, flags) end

---@param label string
---@param hint string
---@param text string
---@param buf_size integer
---@param flags integer
---@param callback fun(data: ImGuiInputTextCallbackData): number
---@return string
---@return boolean
function ImGui.InputTextWithHint(label, hint, text, buf_size, flags, callback) end

---@param label string
---@param v number
---@return number
---@return boolean
function ImGui.InputFloat(label, v) end

---@param label string
---@param v number
---@param step number
---@return number
---@return boolean
function ImGui.InputFloat(label, v, step) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@return number
---@return boolean
function ImGui.InputFloat(label, v, step, step_fast) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@param format string
---@return number
---@return boolean
function ImGui.InputFloat(label, v, step, step_fast, format) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.InputFloat(label, v, step, step_fast, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputFloat2(label, v) end

---@param label string
---@param v table
---@param format string
---@return table
---@return boolean
function ImGui.InputFloat2(label, v, format) end

---@param label string
---@param v table
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.InputFloat2(label, v, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputFloat3(label, v) end

---@param label string
---@param v table
---@param format string
---@return table
---@return boolean
function ImGui.InputFloat3(label, v, format) end

---@param label string
---@param v table
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.InputFloat3(label, v, format, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputFloat4(label, v) end

---@param label string
---@param v table
---@param format string
---@return table
---@return boolean
function ImGui.InputFloat4(label, v, format) end

---@param label string
---@param v table
---@param format string
---@param flags integer
---@return table
---@return boolean
function ImGui.InputFloat4(label, v, format, flags) end

---@param label string
---@param v integer
---@return integer
---@return boolean
function ImGui.InputInt(label, v) end

---@param label string
---@param v integer
---@param step integer
---@return integer
---@return boolean
function ImGui.InputInt(label, v, step) end

---@param label string
---@param v integer
---@param step integer
---@param step_fast integer
---@return integer
---@return boolean
function ImGui.InputInt(label, v, step, step_fast) end

---@param label string
---@param v integer
---@param step integer
---@param step_fast integer
---@param flags integer
---@return integer
---@return boolean
function ImGui.InputInt(label, v, step, step_fast, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputInt2(label, v) end

---@param label string
---@param v table
---@param flags integer
---@return table
---@return boolean
function ImGui.InputInt2(label, v, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputInt3(label, v) end

---@param label string
---@param v table
---@param flags integer
---@return table
---@return boolean
function ImGui.InputInt3(label, v, flags) end

---@param label string
---@param v table
---@return table
---@return boolean
function ImGui.InputInt4(label, v) end

---@param label string
---@param v table
---@param flags integer
---@return table
---@return boolean
function ImGui.InputInt4(label, v, flags) end

---@param label string
---@param v number
---@return number
---@return boolean
function ImGui.InputDouble(label, v) end

---@param label string
---@param v number
---@param step number
---@return number
---@return boolean
function ImGui.InputDouble(label, v, step) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@return number
---@return boolean
function ImGui.InputDouble(label, v, step, step_fast) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@param format string
---@return number
---@return boolean
function ImGui.InputDouble(label, v, step, step_fast, format) end

---@param label string
---@param v number
---@param step number
---@param step_fast number
---@param format string
---@param flags integer
---@return number
---@return boolean
function ImGui.InputDouble(label, v, step, step_fast, format, flags) end

function ImGui.InputScalar() end

function ImGui.InputScalarN() end

---@param label string
---@param col table
---@return table
---@return boolean
function ImGui.ColorEdit3(label, col) end

---@param label string
---@param col table
---@param flags integer
---@return table
---@return boolean
function ImGui.ColorEdit3(label, col, flags) end

---@param label string
---@param col table
---@return table
---@return boolean
function ImGui.ColorEdit4(label, col) end

---@param label string
---@param col table
---@param flags integer
---@return table
---@return boolean
function ImGui.ColorEdit4(label, col, flags) end

---@param label string
---@param col table
---@return table
---@return boolean
function ImGui.ColorPicker3(label, col) end

---@param label string
---@param col table
---@param flags integer
---@return table
---@return boolean
function ImGui.ColorPicker3(label, col, flags) end

---@param label string
---@param col table
---@return table
---@return boolean
function ImGui.ColorPicker4(label, col) end

---@param label string
---@param col table
---@param flags integer
---@return table
---@return boolean
function ImGui.ColorPicker4(label, col, flags) end

---@param desc_id string
---@param col table
---@return boolean
function ImGui.ColorButton(desc_id, col) end

---@param desc_id string
---@param col table
---@param flags integer
---@return boolean
function ImGui.ColorButton(desc_id, col, flags) end

---@param desc_id string
---@param col table
---@param flags integer
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.ColorButton(desc_id, col, flags, sizeX, sizeY) end

---@param flags integer
function ImGui.SetColorEditOptions(flags) end

---@param label string
---@return boolean
function ImGui.TreeNode(label) end

---@param label string
---@param fmt string
---@return boolean
function ImGui.TreeNode(label, fmt) end

---@param label string
---@return boolean
function ImGui.TreeNodeEx(label) end

---@param label string
---@param flags integer
---@return boolean
function ImGui.TreeNodeEx(label, flags) end

---@param label string
---@param flags integer
---@param fmt string
---@return boolean
function ImGui.TreeNodeEx(label, flags, fmt) end

---@param str_id string
function ImGui.TreePush(str_id) end

function ImGui.TreePop() end

---@return number
function ImGui.GetTreeNodeToLabelSpacing() end

---@param label string
---@return boolean
function ImGui.CollapsingHeader(label) end

---@param label string
---@param flags integer
---@return boolean
function ImGui.CollapsingHeader(label, flags) end

---@param label string
---@param open boolean
---@return boolean
---@return boolean open
function ImGui.CollapsingHeader(label, open) end

---@param label string
---@param open boolean
---@param flags integer
---@return boolean
---@return boolean open
function ImGui.CollapsingHeader(label, open, flags) end

---@param is_open boolean
function ImGui.SetNextItemOpen(is_open) end

---@param is_open boolean
---@param cond integer
function ImGui.SetNextItemOpen(is_open, cond) end

---@param label string
---@return boolean
function ImGui.Selectable(label) end

---@param label string
---@param selected boolean
---@return boolean
function ImGui.Selectable(label, selected) end

---@param label string
---@param selected boolean
---@param flags integer
---@return boolean
function ImGui.Selectable(label, selected, flags) end

---@param label string
---@param selected boolean
---@param flags integer
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.Selectable(label, selected, flags, sizeX, sizeY) end

---@param label string
---@param current_item integer
---@param items table
---@param items_count integer
---@return integer
---@return boolean
function ImGui.ListBox(label, current_item, items, items_count) end

---@param label string
---@param current_item integer
---@param items table
---@param items_count integer
---@param height_in_items integer
---@return integer
---@return boolean
function ImGui.ListBox(label, current_item, items, items_count, height_in_items) end

---@param label string
---@return boolean
function ImGui.BeginListBox(label) end

---@param label string
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.BeginListBox(label, sizeX, sizeY) end

function ImGui.EndListBox() end

---@param prefix string
---@param b boolean
function ImGui.Value(prefix, b) end

---@param prefix string
---@param v integer
function ImGui.Value(prefix, v) end

---@param prefix string
---@param v integer
function ImGui.Value(prefix, v) end

---@param prefix string
---@param v number
function ImGui.Value(prefix, v) end

---@param prefix string
---@param v number
---@param float_format string
function ImGui.Value(prefix, v, float_format) end

---@return boolean
function ImGui.BeginMenuBar() end

function ImGui.EndMenuBar() end

---@return boolean
function ImGui.BeginMainMenuBar() end

function ImGui.EndMainMenuBar() end

---@param label string
---@return boolean
function ImGui.BeginMenu(label) end

---@param label string
---@param enabled boolean
---@return boolean
function ImGui.BeginMenu(label, enabled) end

function ImGui.EndMenu() end

---@param label string
---@return boolean
function ImGui.MenuItem(label) end

---@param label string
---@param shortcut string?
---@return boolean
function ImGui.MenuItem(label, shortcut) end

---@param label string
---@param shortcut string?
---@param selected boolean
---@return boolean
---@return boolean
function ImGui.MenuItem(label, shortcut, selected) end

---@param label string
---@param shortcut string?
---@param selected boolean
---@param enabled boolean
---@return boolean
---@return boolean
function ImGui.MenuItem(label, shortcut, selected, enabled) end

function ImGui.BeginTooltip() end

function ImGui.EndTooltip() end

---@param fmt string
function ImGui.SetTooltip(fmt) end

function ImGui.SetTooltipV() end

---@param str_id string
---@return boolean
function ImGui.BeginPopup(str_id) end

---@param str_id string
---@param flags integer
---@return boolean
function ImGui.BeginPopup(str_id, flags) end

---@param name string
---@return boolean
function ImGui.BeginPopupModal(name) end

---@param name string
---@param flags integer
---@return boolean
function ImGui.BeginPopupModal(name, flags) end

---@param name string
---@param open boolean
---@return boolean
function ImGui.BeginPopupModal(name, open) end

---@param name string
---@param open boolean
---@param flags integer
---@return boolean
function ImGui.BeginPopupModal(name, open, flags) end

function ImGui.EndPopup() end

---@param str_id string
function ImGui.OpenPopup(str_id) end

---@param str_id string
---@param popup_flags integer
function ImGui.OpenPopup(str_id, popup_flags) end

function ImGui.CloseCurrentPopup() end

---@return boolean
function ImGui.BeginPopupContextItem() end

---@param str_id string
---@return boolean
function ImGui.BeginPopupContextItem(str_id) end

---@param str_id string
---@param popup_flags integer
---@return boolean
function ImGui.BeginPopupContextItem(str_id, popup_flags) end

---@return boolean
function ImGui.BeginPopupContextWindow() end

---@param str_id string
---@return boolean
function ImGui.BeginPopupContextWindow(str_id) end

---@param str_id string
---@param popup_flags integer
---@return boolean
function ImGui.BeginPopupContextWindow(str_id, popup_flags) end

---@return boolean
function ImGui.BeginPopupContextVoid() end

---@param str_id string
---@return boolean
function ImGui.BeginPopupContextVoid(str_id) end

---@param str_id string
---@param popup_flags integer
---@return boolean
function ImGui.BeginPopupContextVoid(str_id, popup_flags) end

---@param str_id string
---@return boolean
function ImGui.IsPopupOpen(str_id) end

---@param str_id string
---@param popup_flags integer
---@return boolean
function ImGui.IsPopupOpen(str_id, popup_flags) end

---@param str_id string
---@param columns integer
---@return boolean
function ImGui.BeginTable(str_id, columns) end

---@param str_id string
---@param columns integer
---@param flags integer
---@return boolean
function ImGui.BeginTable(str_id, columns, flags) end

---@param str_id string
---@param columns integer
---@param flags integer
---@param outer_sizeX number
---@param outer_sizeY number
---@return boolean
function ImGui.BeginTable(str_id, columns, flags, outer_sizeX, outer_sizeY) end

---@param str_id string
---@param columns integer
---@param flags integer
---@param outer_sizeX number
---@param outer_sizeY number
---@param inner_width number
---@return boolean
function ImGui.BeginTable(str_id, columns, flags, outer_sizeX, outer_sizeY, inner_width) end

function ImGui.EndTable() end

function ImGui.TableNextRow() end

---@param flags integer
function ImGui.TableNextRow(flags) end

---@param flags integer
---@param min_row_height number
function ImGui.TableNextRow(flags, min_row_height) end

---@return boolean
function ImGui.TableNextColumn() end

---@param column_n integer
---@return boolean
function ImGui.TableSetColumnIndex(column_n) end

---@param label string
function ImGui.TableSetupColumn(label) end

---@param label string
---@param flags integer
function ImGui.TableSetupColumn(label, flags) end

---@param label string
---@param flags integer
---@param init_width_or_weight number
function ImGui.TableSetupColumn(label, flags, init_width_or_weight) end

---@param label string
---@param flags integer
---@param init_width_or_weight number
---@param user_id integer
function ImGui.TableSetupColumn(label, flags, init_width_or_weight, user_id) end

---@param cols integer
---@param rows integer
function ImGui.TableSetupScrollFreeze(cols, rows) end

function ImGui.TableHeadersRow() end

---@param label string
function ImGui.TableHeader(label) end

---@return ImGuiTableSortSpecs
function ImGui.TableGetSortSpecs() end

---@return integer
function ImGui.TableGetColumnCount() end

---@return integer
function ImGui.TableGetColumnIndex() end

---@return integer
function ImGui.TableGetRowIndex() end

---@return string
function ImGui.TableGetColumnName() end

---@param column_n integer
---@return string
function ImGui.TableGetColumnName(column_n) end

---@return ImGuiTableColumnFlags
function ImGui.TableGetColumnFlags() end

---@param column_n integer
---@return ImGuiTableColumnFlags
function ImGui.TableGetColumnFlags(column_n) end

---@param target integer
---@param color integer
function ImGui.TableSetBgColor(target, color) end

---@param target integer
---@param colR number
---@param colG number
---@param colB number
---@param colA number
function ImGui.TableSetBgColor(target, colR, colG, colB, colA) end

---@param target integer
---@param color integer
---@param column_n integer
function ImGui.TableSetBgColor(target, color, column_n) end

---@param target integer
---@param colR number
---@param colG number
---@param colB number
---@param colA number
---@param column_n integer
function ImGui.TableSetBgColor(target, colR, colG, colB, colA, column_n) end

function ImGui.Columns() end

---@param count integer
function ImGui.Columns(count) end

---@param count integer
---@param id string
function ImGui.Columns(count, id) end

---@param count integer
---@param id string
---@param border boolean
function ImGui.Columns(count, id, border) end

function ImGui.NextColumn() end

---@return integer
function ImGui.GetColumnIndex() end

---@return number
function ImGui.GetColumnWidth() end

---@param column_index integer
---@return number
function ImGui.GetColumnWidth(column_index) end

---@param column_index integer
---@param width number
function ImGui.SetColumnWidth(column_index, width) end

---@return number
function ImGui.GetColumnOffset() end

---@param column_index integer
---@return number
function ImGui.GetColumnOffset(column_index) end

---@param column_index integer
---@param offset_x number
function ImGui.SetColumnOffset(column_index, offset_x) end

---@return integer
function ImGui.GetColumnsCount() end

---@param str_id string
---@return boolean
function ImGui.BeginTabBar(str_id) end

---@param str_id string
---@param flags integer
---@return boolean
function ImGui.BeginTabBar(str_id, flags) end

function ImGui.EndTabBar() end

---@param label string
---@return boolean
function ImGui.BeginTabItem(label) end

---@param label string
---@param flags integer
---@return boolean
function ImGui.BeginTabItem(label, flags) end

---@param label string
---@param open boolean
---@return boolean open
---@return boolean
function ImGui.BeginTabItem(label, open) end

---@param label string
---@param open boolean
---@param flags integer
---@return boolean open
---@return boolean
function ImGui.BeginTabItem(label, open, flags) end

function ImGui.EndTabItem() end

---@param tab_or_docked_window_label string
function ImGui.SetTabItemClosed(tab_or_docked_window_label) end

---@param dockspace_id integer
---@return integer
function ImGui.DockSpace(dockspace_id) end

---@param dockspace_id integer
---@param size_x number
---@param size_y number
---@return integer
function ImGui.DockSpace(dockspace_id, size_x, size_y) end

---@param dockspace_id integer
---@param size_x number
---@param size_y number
---@param flags ImGuiDockNodeFlags|integer
---@return integer
function ImGui.DockSpace(dockspace_id, size_x, size_y, flags) end

---@return integer
function ImGui.DockSpaceOverViewport() end

---@return integer
---@param dockspace_id integer
function ImGui.DockSpaceOverViewport(dockspace_id) end

---@return integer
---@param dockspace_id integer
---@param viewport nil Unused
---@param flags ImGuiDockNodeFlags|integer
function ImGui.DockSpaceOverViewport(dockspace_id, viewport, flags) end

---@param dockspace_id integer
function ImGui.SetNextWindowDockID(dockspace_id) end

---@param dockspace_id integer
---@param cond ImGuiCond|integer
function ImGui.SetNextWindowDockID(dockspace_id, cond) end

---@return integer
function ImGui.GetWindowDockID() end

---@return boolean
function ImGui.IsWindowDocked() end


function ImGui.BeginDisabled() end

---@param disabled boolean
function ImGui.BeginDisabled(disabled) end

function ImGui.EndDisabled() end

---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
---@param intersect_current boolean
function ImGui.PushClipRect(min_x, min_y, max_x, max_y, intersect_current) end

function ImGui.PopClipRect() end

function ImGui.SetItemDefaultFocus() end

function ImGui.SetKeyboardFocusHere() end

---@param offset integer
function ImGui.SetKeyboardFocusHere(offset) end

---@return boolean
function ImGui.IsItemHovered() end

---@param flags integer
---@return boolean
function ImGui.IsItemHovered(flags) end

---@return boolean
function ImGui.IsItemActive() end

---@return boolean
function ImGui.IsItemFocused() end

---@return boolean
function ImGui.IsItemClicked() end

---@param mouse_button integer
---@return boolean
function ImGui.IsItemClicked(mouse_button) end

---@return boolean
function ImGui.IsItemVisible() end

---@return boolean
function ImGui.IsItemEdited() end

---@return boolean
function ImGui.IsItemActivated() end

---@return boolean
function ImGui.IsItemDeactivated() end

---@return boolean
function ImGui.IsItemDeactivatedAfterEdit() end

---@return boolean
function ImGui.IsItemToggledOpen() end

---@return boolean
function ImGui.IsAnyItemHovered() end

---@return boolean
function ImGui.IsAnyItemActive() end

---@return boolean
function ImGui.IsAnyItemFocused() end

---@return number
---@return number
function ImGui.GetItemRectMin() end

---@return number
---@return number
function ImGui.GetItemRectMax() end

---@return number
---@return number
function ImGui.GetItemRectSize() end

function ImGui.SetItemAllowOverlap() end

---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.IsRectVisible(sizeX, sizeY) end

---@param minX number
---@param minY number
---@param maxX number
---@param maxY number
---@return boolean
function ImGui.IsRectVisible(minX, minY, maxX, maxY) end

---@return number
function ImGui.GetTime() end

---@return integer
function ImGui.GetFrameCount() end

---@return ImDrawList
function ImGui.GetBackgroundDrawList() end

---@return ImDrawList
function ImGui.GetForegroundDrawList() end

---@param idx integer
---@return string
function ImGui.GetStyleColorName(idx) end

---@param id integer
---@param sizeX number
---@param sizeY number
---@return boolean
function ImGui.BeginChildFrame(id, sizeX, sizeY) end

---@param id integer
---@param sizeX number
---@param sizeY number
---@param flags integer
---@return boolean
function ImGui.BeginChildFrame(id, sizeX, sizeY, flags) end

function ImGui.EndChildFrame() end

---@return ImGuiIO
function ImGui.GetIO() end

---@return ImGuiStyle
function ImGui.GetStyle() end

---@param text string
---@return number
---@return number
function ImGui.CalcTextSize(text) end

---@param text string
---@param hide_text_after_double_hash boolean
---@return number
---@return number
function ImGui.CalcTextSize(text, hide_text_after_double_hash) end

---@param text string
---@param hide_text_after_double_hash boolean
---@param wrap_width number
---@return number
---@return number
function ImGui.CalcTextSize(text, hide_text_after_double_hash, wrap_width) end

---@param input integer
---@return table
function ImGui.ColorConvertU32ToFloat4(input) end

---@param rgba table
---@return integer
function ImGui.ColorConvertFloat4ToU32(rgba) end

---@param r number
---@param g number
---@param b number
---@return number
---@return number
---@return number
function ImGui.ColorConvertRGBtoHSV(r, g, b) end

---@param h number
---@param s number
---@param v number
---@return number
---@return number
---@return number
function ImGui.ColorConvertHSVtoRGB(h, s, v) end

---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
---@return boolean
function ImGui.IsMouseHoveringRect(min_x, min_y, max_x, max_y) end

---@param min_x number
---@param min_y number
---@param max_x number
---@param max_y number
---@param clip boolean
---@return boolean
function ImGui.IsMouseHoveringRect(min_x, min_y, max_x, max_y, clip) end

---@return number
---@return number
function ImGui.GetMousePos() end

function ImGui.TeleportMousePos(x, y) end

---@return number
---@return number
function ImGui.GetMousePosOnOpeningCurrentPopup() end

---@param button integer
---@return boolean
function ImGui.IsMouseDragging(button) end

---@param button integer
---@param lock_threshold number
---@return boolean
function ImGui.IsMouseDragging(button, lock_threshold) end

---@return number
---@return number
function ImGui.GetMouseDragDelta() end

---@param button integer
---@return number
---@return number
function ImGui.GetMouseDragDelta(button) end

---@param button integer
---@param lock_threshold number
---@return number
---@return number
function ImGui.GetMouseDragDelta(button, lock_threshold) end

function ImGui.ResetMouseDragDelta() end

---@param button integer
function ImGui.ResetMouseDragDelta(button) end

---@return string
function ImGui.GetClipboardText() end

---@param text string
function ImGui.SetClipboardText(text) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param col integer
function ImGui.ImDrawListAddLine(drawlist, p1X, p1Y, p2X, p2Y, col) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param col integer
---@param thickness number
function ImGui.ImDrawListAddLine(drawlist, p1X, p1Y, p2X, p2Y, col, thickness) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
function ImGui.ImDrawListAddRect(drawlist, p_minX, p_minY, p_maxX, p_maxY, col) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
---@param rounding number
function ImGui.ImDrawListAddRect(drawlist, p_minX, p_minY, p_maxX, p_maxY, col, rounding) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
---@param rounding number
---@param flags integer
function ImGui.ImDrawListAddRect(drawlist, p_minX, p_minY, p_maxX, p_maxY, col, rounding, flags) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
---@param rounding number
---@param flags integer
---@param thickness number
function ImGui.ImDrawListAddRect(drawlist, p_minX, p_minY, p_maxX, p_maxY, col, rounding, flags, thickness) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
function ImGui.ImDrawListAddRectFilled(drawlist, p_minX, p_minY, p_maxX, p_maxY, col) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
---@param rounding number
function ImGui.ImDrawListAddRectFilled(drawlist, p_minX, p_minY, p_maxX, p_maxY, col, rounding) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col integer
---@param rounding number
---@param flags integer
function ImGui.ImDrawListAddRectFilled(drawlist, p_minX, p_minY, p_maxX, p_maxY, col, rounding, flags) end

---@param drawlist ImDrawList
---@param p_minX number
---@param p_minY number
---@param p_maxX number
---@param p_maxY number
---@param col_upr_left integer
---@param col_upr_right integer
---@param col_bot_right integer
---@param col_bot_left integer
function ImGui.ImDrawListAddRectFilledMultiColor(drawlist, p_minX, p_minY, p_maxX, p_maxY, col_upr_left, col_upr_right,
												 col_bot_right, col_bot_left) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param p4X number
---@param p4Y number
---@param col integer
function ImGui.ImDrawListAddQuad(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, p4X, p4Y, col) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param p4X number
---@param p4Y number
---@param col integer
---@param thickness number
function ImGui.ImDrawListAddQuad(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, p4X, p4Y, col, thickness) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param p4X number
---@param p4Y number
---@param col integer
function ImGui.ImDrawListAddQuadFilled(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, p4X, p4Y, col) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param col integer
function ImGui.ImDrawListAddTriangle(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, col) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param col integer
---@param thickness number
function ImGui.ImDrawListAddTriangle(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, col, thickness) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param col integer
function ImGui.ImDrawListAddTriangleFilled(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, col) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
function ImGui.ImDrawListAddCircle(drawlist, centerX, centerY, radius, col) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
function ImGui.ImDrawListAddCircle(drawlist, centerX, centerY, radius, col, num_segments) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
---@param thickness number
function ImGui.ImDrawListAddCircle(drawlist, centerX, centerY, radius, col, num_segments, thickness) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
function ImGui.ImDrawListAddCircleFilled(drawlist, centerX, centerY, radius, col) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
function ImGui.ImDrawListAddCircleFilled(drawlist, centerX, centerY, radius, col, num_segments) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
function ImGui.ImDrawListAddNgon(drawlist, centerX, centerY, radius, col, num_segments) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
---@param thickness number
function ImGui.ImDrawListAddNgon(drawlist, centerX, centerY, radius, col, num_segments, thickness) end

---@param drawlist ImDrawList
---@param centerX number
---@param centerY number
---@param radius number
---@param col integer
---@param num_segments integer
function ImGui.ImDrawListAddNgonFilled(drawlist, centerX, centerY, radius, col, num_segments) end

---@param drawlist ImDrawList
---@param posX number
---@param posY number
---@param col integer
---@param text_begin string
function ImGui.ImDrawListAddText(drawlist, posX, posY, col, text_begin) end

---@param drawlist ImDrawList
---@param font_size number
---@param posX number
---@param posY number
---@param col integer
---@param text_begin string
function ImGui.ImDrawListAddText(drawlist, font_size, posX, posY, col, text_begin) end

---@param drawlist ImDrawList
---@param font_size number
---@param posX number
---@param posY number
---@param col integer
---@param text_begin string
---@param wrap_width number
function ImGui.ImDrawListAddText(drawlist, font_size, posX, posY, col, text_begin, wrap_width) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param p4X number
---@param p4Y number
---@param col integer
---@param thickness number
function ImGui.ImDrawListAddBezierCubic(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, p4X, p4Y, col, thickness) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param p4X number
---@param p4Y number
---@param col integer
---@param thickness number
---@param num_segments integer
function ImGui.ImDrawListAddBezierCubic(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, p4X, p4Y, col, thickness, num_segments) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param col integer
---@param thickness number
function ImGui.ImDrawListAddBezierQuadratic(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, col, thickness) end

---@param drawlist ImDrawList
---@param p1X number
---@param p1Y number
---@param p2X number
---@param p2Y number
---@param p3X number
---@param p3Y number
---@param col integer
---@param thickness number
---@param num_segments integer
function ImGui.ImDrawListAddBezierQuadratic(drawlist, p1X, p1Y, p2X, p2Y, p3X, p3Y, col, thickness, num_segments) end

--#endregion
