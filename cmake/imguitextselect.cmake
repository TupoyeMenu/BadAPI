include(FetchContent)
FetchContent_Declare(
    imguitextselect
    GIT_REPOSITORY https://github.com/AidanSun05/ImGuiTextSelect.git
    GIT_TAG        6e7b369a1c3783189a75fb9f1e44e939987b3953
    GIT_PROGRESS TRUE
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
