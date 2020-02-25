cmake_minimum_required (VERSION 3.8)

project(DefaultSender)
ADD_LIBRARY(DefaultSenderLib STATIC curlsender.cpp)

add_custom_target(libs)

if (MSVC)
find_package(CURL CONFIG REQUIRED)
else (MSVC)
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
target_link_libraries(DefaultSenderLib PRIVATE -lssl)
target_link_libraries(DefaultSenderLib PRIVATE -lcrypto)
include(openssl.cmake)
include(curl.cmake)
add_dependencies(openssl libs)
add_dependencies(curl libs)
set(openssl_INCLUDE_DIRS  "${CMAKE_CURRENT_BINARY_DIR}/openssl-src/include"
	    	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
set(curl_INCLUDE_DIRS  "${CMAKE_CURRENT_BINARY_DIR}/curl-src/include"                                                             CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
endif (MSVC)

if(DEFINED ENV{INCLUDE_PATH})
endif()

if(DEFINED ENV{INSTALL_LIB_PATH})
target_link_libraries(DefaultSenderLib PRIVATE -L$ENV{INSTALL_LIB_PATH})
endif()

target_link_libraries(DefaultSenderLib PRIVATE ${CURL_LIBRARIES})
target_include_directories(DefaultSenderLib PRIVATE ${CURL_INCLUDE_DIRS})

include_directories(include ${DevicePushNotification_INCLUDE_DIRS} ${openssl_INCLUDE_DIRS} ${curl_INCLUDE_DIRS})
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

