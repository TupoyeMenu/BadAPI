include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        c3fcafdc10146beb5919319d0683e44e3c30d537
    GIT_PROGRESS TRUE
)
message("MinHook")
FetchContent_MakeAvailable(minhook)
set_property(TARGET minhook PROPERTY CXX_STANDARD 20)
