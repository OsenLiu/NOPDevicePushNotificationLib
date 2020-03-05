cmake_minimum_required (VERSION 3.8)

project(DefaultSender)
ADD_LIBRARY(DefaultSenderLib STATIC curlsender.cpp)

if(NOT DEFINED INSTALL_LIB_PATH)
set(BUILD_OPENSSL true)
set(BUILD_CURL true)
endif()

message(STATUS ${CURL_LIBRARY_DIR})
if(DEFINED CURL_LIBRARY_DIR)
message(STATUS "find curl in ${CURL_LIBRARY_DIR}/libcurl.a")
add_library(curl STATIC IMPORTED)
set_property(TARGET curl PROPERTY IMPORTED_LOCATION ${CURL_LIBRARY_DIR}/libcurl.a)
set(CURL_LIBRARY ${CURL_LIBRARY_DIR}/libcurl.a)
elseif(MSVC)
find_package(CURL CONFIG REQUIRED)
else()
message("use curl from system")
find_package(CURL REQUIRED)
set(CURL_LIBRARY "-lcurl")
endif()

if(DEFINED OPENSSL_LIBRARY_DIR)
add_library(openssl STATIC IMPORTED)
set_property(TARGET openssl PROPERTY IMPORTED_LOCATION ${OPENSSL_LIBRARY_DIR}/libssl.a)
add_library(crypto STATIC IMPORTED)
set_property(TARGET crypto PROPERTY IMPORTED_LOCATION ${OPENSSL_LIBRARY_DIR}/libcrypto.a)                                      
set(OPENSSL_LIBRARIES "${OPENSSL_LIBRARY_DIR}/libssl.a;${OPENSSL_LIBRARY_DIR}/libcrypto.a")
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
