cmake_minimum_required(VERSION 3.10)
project(CPPHW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)
# Add source files
set(SRC_FILES
    src/product.cpp
    src/logger.cpp
)

# Add GoogleTest
add_subdirectory(external/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
add_executable(MultithreadedTest tests/multithreaded_test.cpp ${SRC_FILES})
target_link_libraries(MultithreadedTest gtest gtest_main pthread)

add_executable(LoggerTest tests/logger_test.cpp ${SRC_FILES})
target_link_libraries(LoggerTest gtest gtest_main pthread)
