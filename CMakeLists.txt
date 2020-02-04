# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

SET(CMAKE_SYSTEM_NAME Linux)

if(EXISTS "$ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}gcc")
SET(CMAKE_C_COMPILER $ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}gcc)
SET(CMAKE_CXX_COMPILER $ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}g++)
endif()

project ("NOPDevicePushNotification")

# Include sub-projects.
add_subdirectory ("device_push_notification")
add_subdirectory ("curl")
include(CTest)
add_subdirectory ("test")

