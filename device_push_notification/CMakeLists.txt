# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(DevicePushNotification)
include_directories(include)

ADD_LIBRARY(DevicePushNotificationLib STATIC pushnotification.cpp base64.cpp payload.cpp)

if(BUILD_SHARED_NOP)
ADD_LIBRARY(DevicePushNotification SHARED pushnotification.cpp base64.cpp payload.cpp)
endif(BUILD_SHARED_NOP)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

