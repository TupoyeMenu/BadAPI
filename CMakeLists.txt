cmake_minimum_required(VERSION 3.20)

# Crosscompiling
include(cmake/crosscompile.cmake)

project(BadAPI CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Fetch modules
message("\nFetching modules")
include(cmake/minhook.cmake)
include(cmake/async-logger.cmake)
include(cmake/json.cmake)
include(cmake/luajit.cmake)

message("\nFetching custom modules")
include(cmake/imgui.cmake)
include(cmake/utfcpp.cmake)
include(cmake/imguitextselect.cmake)
include(cmake/gtav-classes.cmake)

set(RESOURCES
    "${minhook_SOURCE_DIR}/dll_resources/MinHook.def"
)

# BigBaseV2
message(STATUS ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)
add_library(${CMAKE_PROJECT_NAME} MODULE "${SRC_MAIN}" ${RESOURCES})


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 23)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}"
    "${minhook_SOURCE_DIR}/src/hde"
    "${luajit_SOURCE_DIR}/src"
    "${luajit_BINARY_DIR}/src"
    "${imguitextselect_SOURCE_DIR}"
)

target_precompile_headers(${CMAKE_PROJECT_NAME} PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE minhook AsyncLogger dbghelp imgui imguitextselect libluajit d3dcompiler dwmapi winmm psapi dxgi)

add_compile_definitions(
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
    "_WIN32_WINNT=0x0600"
    "CXX_FORMAT_SUPPORT"
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE PROJECT_NAME="${CMAKE_PROJECT_NAME}")
