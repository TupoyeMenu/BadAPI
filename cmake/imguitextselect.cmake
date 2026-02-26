include(FetchContent)
FetchContent_Declare(
    imguitextselect
    GIT_REPOSITORY https://github.com/AidanSun05/ImGuiTextSelect.git
    GIT_TAG        afb8a11910be6c77ac4b4535f694e14f5bbb5bc3
    GIT_PROGRESS TRUE
    SOURCE_SUBDIR "why" # Force cmake to not use CMakeFiles included in the repo
)

message("ImGuiTextSelect")

FetchContent_MakeAvailable(imguitextselect)
file(GLOB SRC_IMGUI_TEXT_SELECT
    "${imguitextselect_SOURCE_DIR}/textselect.cpp"
)

add_library(imguitextselect STATIC ${SRC_IMGUI_TEXT_SELECT})
source_group(TREE ${imguitextselect_SOURCE_DIR} PREFIX "imguitextselect" FILES ${SRC_IMGUI_TEXT_SELECT} )
target_include_directories(imguitextselect PRIVATE
    "${imguitextselect_SOURCE_DIR}"
	"${imgui_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}/backends"
    "${imgui_SOURCE_DIR}/misc/cpp"
    "${utfcpp_SOURCE_DIR}/source"
)

set_property(TARGET imguitextselect PROPERTY CXX_STANDARD 20)
