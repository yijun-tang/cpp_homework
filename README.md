# C++ Homework
DexMate C++ homework for interview

## Setup
This project is using C++ 17, any compilers compatiable with this version should be working. I developed it by clang (`clang-1403.0.22.14.1`) on macOS (M1 pro chip). But it doesn't use any special features specific to clang, so g++ should be ok.

If you don't have C++ 17 compiler on your machine, you should install it first. I would recommend the clang compiler which is providing more friendly message, especially useful for debugging. Another needed tool is cmake to build the project. The version of cmake should be 3.10+.

## Running Unit Tests
```sh
# build project
mkdir -p build && cd build
cmake ..                        # build again if CMakeLists.txt is modified
cmake cmake --build .           # build again if source code is modified

# running unit tests for `Logger`
./LoggerTest

# running unit tests for Concurrent suppilers and checker for `Warehouse`
./MultithreadedTest

# running unit tests for simple unit testing framework
./TestFrameworkTest
```

_Note: this project doesn't provide binary to run directly, if you want to reuse some functionality of it, please import it as third party library._
