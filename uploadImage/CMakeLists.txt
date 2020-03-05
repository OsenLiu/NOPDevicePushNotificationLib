# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(UploadImage)

ADD_LIBRARY(UploadImageLib STATIC uploadimage.cpp)
include_directories(include ${DevicePushNotification_INCLUDE_DIRS} ${DefaultSender_INCLUDE_DIRS})

target_link_libraries(UploadImageLib DefaultSenderLib)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

