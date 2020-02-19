# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)


execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(${result})
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(${result})
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# GTest

#include(nlohmann_json.cmake)
#set(JSON_BuildTests OFF CACHE INTERNAL "")
#set(nlohmann_json_INCLUDE_DIRS  "${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src/include"
#	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
#set(JSON_BuildTests OFF CACHE INTERNAL "")
#add_subdirectory(nlohmann_json)
#nlohmann_json

project (NOPPush.Test)
add_executable(NOPPush.Test 
	main.cpp
	tst_send_push.cpp
	tst_dvr_real_send.cpp
    tst_standalone_real_send.cpp
    printfLogger.cpp
)

include_directories(${CMAKE_SOURCE_DIR} 
	${DevicePushNotification_INCLUDE_DIRS}
    ${DefaultSender_INCLUDE_DIRS}
	${GTEST_INCLUDE_DIRS}
    ${nlohmann_json_INCLUDE_DIRS}
)
target_link_libraries(NOPPush.Test gtest_main gmock_main DevicePushNotificationLib DefaultSenderLib)
#target_link_libraries(NOPPush.Test PRIVATE nlohmann_json::nlohmann_json)
add_test(NAME "push_test" COMMAND "NOPPush.Test")