include(FetchContent)

set(ZLIB_COMPAT ON CACHE INTERNAL "" FORCE)
set(ZLIB_ENABLE_TESTS OFF CACHE INTERNAL "" FORCE)

FetchContent_Declare(zlib
    GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng
    GIT_TAG 2.1.3
    OVERRIDE_FIND_PACKAGE
    USES_TERMINAL_DOWNLOAD TRUE
)
message("zlib")
FetchContent_MakeAvailable(zlib)

set(ZLIB_INCLUDE_DIR ${zlib_BINARY_DIR})
