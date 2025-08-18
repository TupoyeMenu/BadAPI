include(FetchContent)

set(ENABLE_TAR OFF)
set(ENABLE_CPIO OFF)
set(ENABLE_CAT OFF)
set(ENABLE_UNZIP OFF)
set(ENABLE_TEST OFF)
set(ENABLE_INSTALL OFF)
set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    libarchive
    GIT_REPOSITORY https://github.com/libarchive/libarchive.git
    GIT_TAG        v3.8.1
    GIT_PROGRESS TRUE
)
message("libarchive")
FetchContent_MakeAvailable(libarchive)

set_property(TARGET archive_static PROPERTY COMPILE_WARNING_AS_ERROR OFF)
target_compile_definitions(archive_static PRIVATE
    "_CRT_SECURE_NO_WARNINGS"
)
