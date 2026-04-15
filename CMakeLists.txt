cmake_minimum_required(VERSION 3.16)
project(
  TicTacToeModelProject VERSION 1.0
  DESCRIPTION "Tictactoe service model structures."
  LANGUAGES CXX C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS_TSAN "-O1 -g -fsanitize=thread -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_TSAN "-O1 -g -fsanitize=thread -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS_TSAN "-fsanitize=thread")
set(CMAKE_SHARED_LINKER_FLAGS_TSAN "-fsanitize=thread")

# set everything up for c++ 20 features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(tttmodel)

option(BUILD_TTTMODEL_TESTS "Build tests" OFF)

if(BUILD_TTTMODEL_TESTS)

  find_package(PkgConfig REQUIRED)
  pkg_check_modules(LIBPQ REQUIRED libpq)

  if(LIBPQ_FOUND)
    message("-- libpq found via pkg-config")
    message("-- Include dirs: ${LIBPQ_INCLUDE_DIRS}")
    message("-- Libraries: ${LIBPQ_LIBRARIES}")
    message("-- CFLAGS: ${LIBPQ_CFLAGS_OTHER}")
    add_compile_definitions(LIBPQ_FOUND)
  else()
    message(FATAL_ERROR "libpq not found via pkg-config")
  endif()

  include(FetchContent)
  FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
  )
  FetchContent_MakeAvailable(nlohmann_json)
  target_link_libraries(TTTModel PUBLIC nlohmann_json::nlohmann_json ${LIBPQ_LIBRARIES})
  target_include_directories(TTTModel PUBLIC $<BUILD_INTERFACE:${LIBPQ_INCLUDE_DIRS}>)

  add_subdirectory(test)

endif()

