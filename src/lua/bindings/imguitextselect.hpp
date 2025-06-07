#pragma once

namespace lua::imguitextselect
{
	// Lua API: Class
	// Name: text_select
	// Class representing a text_select object.

	// Lua API: Constructor
	// Class: text_select
	// Param: getLineAtIdx: function: Function taking a line number and returning the string in that line
	// Param: getNumLines: function: Function returning the total number of lines of text
	// Param: enableWordWrap: boolean
	// Returns: text_select: An instance of text_select.

	
	// Lua API: Function
	// Class: text_select
	// Name: hasSelection
	// Returns: boolean
	// Checks if there is an active selection in the text.

	// Lua API: Function
	// Class: text_select
	// Name: copy
	// Copies the selected text to the clipboard.

	// Lua API: Function
	// Class: text_select
	// Name: selectAll
	// Selects all text in the window.

	// Lua API: Function
	// Class: text_select
	// Name: update
	// Draws the text selection rectangle and handles user input.

	void bind(sol::state& state);
}