# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("NOPDevicePushNotification")

# Include sub-projects.
add_subdirectory ("device_push_notification")
add_subdirectory ("curl")
include(CTest)
add_subdirectory ("test")

