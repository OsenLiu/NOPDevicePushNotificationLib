# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(DevicePushNotification)
include_directories(include)

ADD_LIBRARY(DevicePushNotificationLib STATIC pushnotification.cpp base64.cpp)

