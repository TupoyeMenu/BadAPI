include(FetchContent)

message("LuaJIT")

# For some reason putting this into crosscompile.cmake doesn't work.
if(CROSSCOMPILE)
    set(CMAKE_SYSTEM_VERSION 10.0.26100)
endif()
set(LUAJIT_BUILD_TOOL OFF)
set(LUAJIT_FORCE_UTF8_FOPEN ON)

FetchContent_Declare(
    luajit
    GIT_REPOSITORY https://github.com/WohlSoft/LuaJIT.git
    GIT_TAG 27878965958986687f8caaf8a2b6b73bc5df85e0
    GIT_PROGRESS TRUE
)

add_compile_definitions("_CRT_SECURE_NO_WARNINGS")
FetchContent_MakeAvailable(luajit)
