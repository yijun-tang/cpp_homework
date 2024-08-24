#include "logger.h"

// Initialize the singleton instance
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

// Private constructor
Logger::Logger() {
    logFile.open(LOG_FILE_NAME, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}

// Private destructor
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

// Log a message with a specific log level
void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open()) {
        logFile << getCurrentTime() << " [" << logLevelToString(level) << "] "
                << message << std::endl;
    }
}

// Flush logs to the file
void Logger::flush() {
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open()) {
        logFile.flush();
    }
}

// Get the current timestamp
std::string Logger::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_time_t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

// Convert log level to string
std::string Logger::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}
