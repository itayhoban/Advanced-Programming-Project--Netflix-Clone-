cmake_minimum_required(VERSION 3.10)

# Project name
project(my_project)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create a library for shared source files
add_library(my_library
    src/Utils.cpp
    src/AddMovieCommand.cpp
    src/HelpCommand.cpp
    src/DisplayRecommendedMoviesCommand.cpp
    src/App.cpp
    src/DeleteCommand.cpp
)

# Main application
add_executable(my_project
    src/ConsoleMenu.cpp
)

# Link the library to the main application
target_link_libraries(my_project my_library)

# Unit tests
add_executable(runTests
    # tests/test_main.cpp
    src/tests/test_utils.cpp
    # src/tests/ConsoleMenuTest.cpp
    src/Utils.cpp
    # src/ConsoleMenu.cpp
    # src/AddMovieCommand.cpp
    # src/HelpCommand.cpp
    # src/DisplayRecommendedMoviesCommand.cpp
    # src/App.cpp
)

# Link the library and Google Test to the test executable
target_link_libraries(runTests my_library gtest_main)

# Enable testing
enable_testing()
include(GoogleTest)
gtest_discover_tests(runTests)
