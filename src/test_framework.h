#ifndef TEST_FRAMEWORK_H_
#define TEST_FRAMEWORK_H_

#include <iostream>
#include <string>

// Macro for asserting equality
#define ASSERT_EQUAL(actual, expected) \
    TestFramework::assertEqual((actual), (expected), __LINE__, __FILE__)

// Macro for asserting boolean conditions
#define ASSERT_TRUE(condition) \
    TestFramework::assertTrue((condition), __LINE__, __FILE__)

#define TEST_CASE(name)                                  \
    void name();                                         \
    static bool name##Registered = []() {                \
        TestFramework::TestRunner::addTest(#name, name); \
        return true;                                     \
    }();                                                 \
    void name()

namespace TestFramework {

// Define a type alias for test functions
using TestFunc = std::function<void()>;

template <typename T>
void assertEqual(const T& actual, const T& expected, int line,
                 const std::string& file);

void assertTrue(bool condition, int line, const std::string& file);

class TestRunner {
   public:
    static void addTest(const std::string& name, TestFunc func) {
        getInstance().tests.emplace_back(name, func);
    }

    static void runTests();

   private:
    std::vector<std::pair<std::string, TestFunc>> tests;

    static TestRunner& getInstance() {
        static TestRunner instance;
        return instance;
    }

    TestRunner() = default;
    TestRunner(const TestRunner&) = delete;
    TestRunner& operator=(const TestRunner&) = delete;
};

}  // namespace TestFramework

#endif  // TEST_FRAMEWORK_H_
