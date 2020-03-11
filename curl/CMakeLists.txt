cmake_minimum_required (VERSION 3.8)

project(DefaultSender)
ADD_LIBRARY(DefaultSenderLib STATIC curlsender.cpp)

if(NOT DEFINED INSTALL_LIB_PATH)
set(BUILD_OPENSSL true)
set(BUILD_CURL true)
endif()

message(STATUS ${CURL_LIBRARY_DIR})
if(DEFINED CURL_LIBRARY_DIR)
SET(CMAKE_LIBRARY_PATH ${CURL_LIBRARY_DIR} ${CMAKE_LIBRARY_PATH})
find_library(libcurl NAMES libcurl.a)
set(CURL_LIBRARY ${libcurl})
elseif(MSVC)
find_package(CURL CONFIG REQUIRED)
else()
message("use curl from system")
find_package(CURL REQUIRED)
set(CURL_LIBRARY "-lcurl")
endif()

if(DEFINED OPENSSL_LIBRARY_DIR)
SET(CMAKE_LIBRARY_PATH ${OPENSSL_LIBRARY_DIR} ${CMAKE_LIBRARY_PATH})
find_library(libssl NAMES libssl.a)
find_library(libcrypto NAMES libcrypto.a)
set(OPENSSL_LIBRARIES ${libssl} ${libcrypto})
else()
set(OPENSSL_LIBRARIES "-lssl;-lcrypto")
endif()

target_link_libraries(DefaultSenderLib ${CURL_LIBRARY} ${OPENSSL_LIBRARIES})
target_include_directories(DefaultSenderLib PUBLIC ${CURL_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIRS})

find_package (Threads)
if(CMAKE_THREAD_LIBS_INIT)
target_link_libraries(DefaultSenderLib ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()
#thread


if(WIN32)
  target_link_libraries(DefaultSenderLib wsock32 ws2_32)
endif()
#socket

include_directories(include ${DevicePushNotification_INCLUDE_DIRS})
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
set(${PROJECT_NAME}_LIBRARIES ${CURL_LIBRARY};${OPENSSL_LIBRARIES}
	        CACHE INTERNAL "${PROJECT_NAME}: curl & ssl lib" FORCE)
