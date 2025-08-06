
include(FetchContent)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/TupoyeMenu/GTAV-Classes.git
    GIT_TAG        0cb51210f40793840d10602f81db4bb9235fe805
    GIT_PROGRESS TRUE
    SOURCE_SUBDIR "why" # FetchContent_Populate is depricated now, so we set this to a non existing directory.
)
message("GTAV-Classes")
FetchContent_MakeAvailable(gtav_classes)
