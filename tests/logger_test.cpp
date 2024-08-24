#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <thread>
#include "../src/logger.h"

// Helper function to clear log file
void clearLogFile() {
    std::ofstream ofs(LOG_FILE_NAME, std::ofstream::trunc);
    ofs.close();
}

TEST(LoggerTest, SingletonTest) {
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();

    EXPECT_EQ(&logger1, &logger2);
}

TEST(LoggerTest, LogFunctionTest) {
    clearLogFile();

    Logger& logger = Logger::getInstance();
    logger.log(LogLevel::INFO, "Test log message");

    std::ifstream logFile(LOG_FILE_NAME);
    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContent = buffer.str();

    EXPECT_NE(logContent.find("Test log message"), std::string::npos);
    EXPECT_NE(logContent.find("[INFO]"), std::string::npos);
}

TEST(LoggerTest, FlushTest) {
    clearLogFile();
    Logger& logger = Logger::getInstance();
    logger.log(LogLevel::INFO, "Before flush");

    logger.flush();
    
    std::ifstream logFile(LOG_FILE_NAME);
    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContent = buffer.str();

    EXPECT_NE(logContent.find("Before flush"), std::string::npos);
}

TEST(LoggerTest, ThreadSafetyTest) {
    clearLogFile();
    const int numThreads = 10;

    auto loggingFunction = [](int threadId) {
        Logger& logger = Logger::getInstance();
        for (int i = 0; i < 100; ++i) {
            logger.log(LogLevel::INFO, "Thread " + std::to_string(threadId) + " log message " + std::to_string(i));
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(loggingFunction, i);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::ifstream logFile(LOG_FILE_NAME);
    std::stringstream buffer;
    buffer << logFile.rdbuf();
    std::string logContent = buffer.str();

    // Verify that the log file contains entries from all threads
    for (int i = 0; i < numThreads; ++i) {
        for (int j = 0; j < 100; ++j) {
            std::string expectedMessage = "Thread " + std::to_string(i) + " log message " + std::to_string(j);
            EXPECT_NE(logContent.find(expectedMessage), std::string::npos);
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
