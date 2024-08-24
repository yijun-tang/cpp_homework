#include "test_framework.h"

#include <string>

template <typename T>
void TestFramework::assertEqual(const T& actual, const T& expected, int line,
                                const std::string& file) {
    if (actual != expected) {
        std::cerr << "Assertion failed at " << file << ":" << line
                  << ": expected " << expected << ", but got " << actual
                  << std::endl;
    }
}

void TestFramework::assertTrue(bool condition, int line,
                               const std::string& file) {
    if (!condition) {
        std::cerr << "Assertion failed at " << file << ":" << line
                  << ": condition is false" << std::endl;
    }
}

void TestFramework::TestRunner::runTests() {
    for (const auto& test : getInstance().tests) {
        std::cout << "Running test: " << test.first << std::endl;
        test.second();
    }
}

template void TestFramework::assertEqual(const int&, const int&, int,
                                         const std::string&);
template void TestFramework::assertEqual(const std::string&, const std::string&,
                                         int, const std::string&);
