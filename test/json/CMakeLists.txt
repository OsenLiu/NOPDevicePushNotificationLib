include(nlohmann_json.cmake)

set(JSON_BuildTests OFF CACHE INTERNAL "")

#add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src)
#add_subdirectory(nlohmann_json)

set(nlohmann_json_INCLUDE_DIRS  "${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src/include"
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src)

ADD_LIBRARY(jsonLib)
target_link_libraries(jsonLib PRIVATE nlohmann_json::nlohmann_json)