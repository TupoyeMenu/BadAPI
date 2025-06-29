#pragma once

namespace lua::vector2
{
	// Lua API: Class
	// Name: vec2
	// Class representing a 2D vector.

	// Lua API: Constructor
	// Class: vec2
	// Param: x: float: x component of the vector.
	// Param: y: float: y component of the vector.
	// Returns: vec2: a vector that contains the x and y values.

	// Lua API: Field
	// Class: vec2
	// Field: x: float
	// x component of the vector.

	// Lua API: Field
	// Class: vec2
	// Field: y: float
	// y component of the vector.

	void bind(sol::state& state);
}
