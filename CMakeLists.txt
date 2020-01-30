# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("NOPDevicePushNotification")

# Include sub-projects.
add_subdirectory ("curl")
add_subdirectory ("device_push_notification")
include(CTest)
add_subdirectory ("test")

