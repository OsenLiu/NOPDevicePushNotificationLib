# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

if (NOT WIN32)
SET(CMAKE_SYSTEM_NAME Linux)
endif()

project ("NOPDevicePushNotification")

# Include sub-projects.
add_subdirectory ("device_push_notification")
add_subdirectory ("uploadImage")
if(ENABLE_TEST)
message(STATUS "All Tests are enabled")
add_subdirectory ("curl")
include(CTest)
add_subdirectory ("test")
endif(ENABLE_TEST)