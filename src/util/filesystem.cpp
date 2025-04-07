#include <filesystem>

namespace big::filesystem
{
	std::optional<std::filesystem::path> make_absolute(const std::filesystem::path& root, const std::filesystem::path& user_path)
	{
		auto final_path = std::filesystem::weakly_canonical(root / user_path);

		auto [root_end, nothing] = std::mismatch(root.begin(), root.end(), final_path.begin());

		if (root_end != root.end())
			return std::nullopt;

		return final_path;
	}
}