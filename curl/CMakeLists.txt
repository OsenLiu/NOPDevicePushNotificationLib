cmake_minimum_required (VERSION 3.8)

project(DefaultSender)
ADD_LIBRARY(DefaultSenderLib STATIC curlsender.cpp)

if (MSVC)
find_package(CURL CONFIG REQUIRED)
else (MSVC)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
target_link_libraries(DefaultSenderLib PRIVATE -lssl)
target_link_libraries(DefaultSenderLib PRIVATE -lcrypto)
endif (MSVC)

if(DEFINED ENV{INCLUDE_PATH})
SET(CURL_INCLUDE_DIRS $ENV{INCLUDE_PATH})
endif()

if(DEFINED ENV{INSTALL_LIB_PATH})
target_link_libraries(DefaultSenderLib PRIVATE -L$ENV{INSTALL_LIB_PATH})
endif()

target_link_libraries(DefaultSenderLib PRIVATE ${CURL_LIBRARIES})
target_include_directories(DefaultSenderLib PRIVATE ${CURL_INCLUDE_DIRS})

include_directories(include ${DevicePushNotification_INCLUDE_DIRS})
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

