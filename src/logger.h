#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>

const std::string LOG_FILE_NAME = "log.txt";

// Log levels enumeration
enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

// Logger class
class Logger {
public:
    // Get the singleton instance of the Logger
    static Logger& getInstance();

    // Log a message with a specific log level
    void log(LogLevel level, const std::string& message);

    // Flush logs to the file
    void flush();

private:
    // Private constructor and destructor for Singleton
    Logger();
    ~Logger();

    // Deleted copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Helper functions
    std::string getCurrentTime() const;
    std::string logLevelToString(LogLevel level) const;

    std::ofstream logFile;
    std::mutex mtx;
};

#endif // LOGGER_H_
