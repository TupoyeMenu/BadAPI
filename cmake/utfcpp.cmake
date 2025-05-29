include(FetchContent)
FetchContent_Declare(
    utfcpp
    GIT_REPOSITORY https://github.com/nemtrif/utfcpp.git
    GIT_TAG        v4.0.6
    GIT_PROGRESS TRUE
	SOURCE_SUBDIR "why" # FetchContent_Populate is depricated now, so we set this to a non existing directory.
)

message("utfcpp")

FetchContent_MakeAvailable(utfcpp)
