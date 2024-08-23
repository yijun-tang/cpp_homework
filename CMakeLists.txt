cmake_minimum_required(VERSION 3.10)
project(CPPHW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CPPHW src/main.cpp)

# Add GoogleTest
add_subdirectory(external/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
add_executable(CPPHWTests tests/test_main.cpp)
target_link_libraries(CPPHWTests gtest gtest_main)

# Enable CTest
enable_testing()
add_test(NAME CPPHWTests COMMAND CPPHWTests)
