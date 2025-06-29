namespace lua::vector2
{
	struct Vector2
	{
		float x = 0.f;
		float y = 0.f;

		Vector2() = default;
		Vector2(float x, float y) :
		    x(x),
		    y(y)
		{
		}

		std::string to_string() const
		{
			char buffer[64]{};
			snprintf(buffer, sizeof(buffer), "(%.3f, %.3f)", x, y);
			return std::string(buffer);
		}
	};

	void bind(sol::state& state)
	{

		auto usertype = state.new_usertype<Vector2>("vec2", sol::constructors<Vector2(float, float)>());

		usertype["x"]          = &Vector2::x;
		usertype["y"]          = &Vector2::y;
		usertype["__tostring"] = &Vector2::to_string;
	}
}
