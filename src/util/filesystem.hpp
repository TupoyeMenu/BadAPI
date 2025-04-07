#pragma once
#include <filesystem>

namespace big::filesystem
{
	std::optional<std::filesystem::path> make_absolute(const std::filesystem::path& root, const std::filesystem::path& user_path);
}
