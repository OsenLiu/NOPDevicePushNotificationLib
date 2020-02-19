include(ExternalProject)

ExternalProject_Add(nlohmann_json
  GIT_REPOSITORY    https://github.com/nlohmann/json.git
  GIT_TAG           master
  SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src"
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

