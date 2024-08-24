# C++ Homework
DexMate C++ homework for interview

## Setup
This project is using C++ 17, any compilers compatiable with this version should be working. I developed it by clang (`clang-1403.0.22.14.1`) on macOS (M1 pro chip). But it doesn't use any special features specific to clang, so g++ should be ok.

If you don't have C++ 17 compiler on your machine, you should install it first. I would recommend the clang compiler which is providing more friendly message, especially useful for debugging. Another needed tool is cmake to build the project. The version of cmake should be 3.10+.

clone repository with `googletest` submodule:
```sh
git clone --recurse-submodules git@github.com:yijun-tang/cpp_homework.git
```

## Running Unit Tests
```sh
# build project
mkdir -p build && cd build
cmake ..                        # build again if CMakeLists.txt is modified
cmake --build .           # build again if source code is modified

# running unit tests for `Logger`
./LoggerTest

# running unit tests for Concurrent suppilers and checker for `Warehouse`
./MultithreadedTest

# running unit tests for simple unit testing framework
./TestFrameworkTest
```
If everything goes well, the message would be something like:
```sh
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from LoggerTest
[ RUN      ] LoggerTest.SingletonTest
[       OK ] LoggerTest.SingletonTest (0 ms)
[ RUN      ] LoggerTest.LogFunctionTest
[       OK ] LoggerTest.LogFunctionTest (0 ms)
[ RUN      ] LoggerTest.FlushTest
[       OK ] LoggerTest.FlushTest (0 ms)
[ RUN      ] LoggerTest.ThreadSafetyTest
[       OK ] LoggerTest.ThreadSafetyTest (18 ms)
[----------] 4 tests from LoggerTest (19 ms total)
[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (19 ms total)
[  PASSED  ] 4 tests.

[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from WarehouseTest
[ RUN      ] WarehouseTest.ConcurrentSupplierAndChecker
...
[       OK ] WarehouseTest.ConcurrentSupplierAndChecker (3098 ms)
[----------] 1 test from WarehouseTest (3099 ms total)
[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (3099 ms total)
[  PASSED  ] 1 test.

Running test: testAddProduct
Running test: testRemoveProduct
Running test: testUpdateProductQuantity
```

_Note: this project doesn't provide binary to run directly, if you want to reuse some functionality of it, please import it as third party library._
