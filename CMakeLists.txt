# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

if (NOT WIN32)
SET(CMAKE_SYSTEM_NAME Linux)
endif()

if((DEFINED ENV{TOOLCHAIN_LIB_PATH}) AND (DEFINED ENV{CROSS_COMPILE}))
SET(CMAKE_C_COMPILER $ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}gcc)
SET(CMAKE_CXX_COMPILER $ENV{TOOLCHAIN_LIB_PATH}/../bin/$ENV{CROSS_COMPILE}g++)
endif()

project ("NOPDevicePushNotification")

# Include sub-projects.
add_subdirectory ("device_push_notification")
add_subdirectory ("curl")
include(CTest)
add_subdirectory ("test")

