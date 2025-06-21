include(FetchContent)

set(USE_FMT OFF)

message("AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG 25b5ed31b33c40fabc6b80213c330a10cccf3b49
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

target_compile_definitions(AsyncLogger PRIVATE CXX_FORMAT_SUPPORT)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 20)
