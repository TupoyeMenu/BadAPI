#include "textselect.hpp"

namespace lua::imguitextselect
{
	void bind(sol::state& state)
	{
		auto usertype = state.new_usertype<TextSelect>("text_select", sol::constructors<TextSelect(std::function<std::string_view(std::size_t)>, std::function<std::size_t()>, bool)>());

		usertype["hasSelection"] = &TextSelect::hasSelection;
		usertype["copy"]         = &TextSelect::copy;
		usertype["selectAll"]    = &TextSelect::selectAll;
		usertype["update"]       = &TextSelect::update;
	}
}
