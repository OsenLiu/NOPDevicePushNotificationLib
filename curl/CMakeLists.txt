cmake_minimum_required (VERSION 3.8)

project(DefaultSender)
ADD_LIBRARY(DefaultSenderLib STATIC curlsender.cpp)


find_package(CURL CONFIG REQUIRED)
target_link_libraries(DefaultSenderLib PRIVATE ${CURL_LIBRARIES})
target_include_directories(DefaultSenderLib PRIVATE ${CURL_INCLUDE_DIRS})

include_directories(include ${CURL_INCLUDE_DIRS}/curl ${DevicePushNotification_SOURCE_DIR}/include)

