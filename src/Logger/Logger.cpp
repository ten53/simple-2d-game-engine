#include "Logger.h"
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <mutex>

// Static mutex definition
std::mutex Logger::logMutex;

std::string Logger::LocalTime() {
    std::time_t now = std::time(nullptr);

    std::tm localTime;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&localTime, &now);
#else
    localtime_r(&now, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::Log(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::cout << "\033[32m" // Green color
              << "LOG: [" << LocalTime() << "] - " << message
              << "\033[0m"  // Reset color
              << std::endl;
}

void Logger::Err(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::cerr << "\033[31m" // Red color
              << "ERROR: [" << LocalTime() << "] - " << message
              << "\033[0m"  // Reset color
              << std::endl;
}

void Logger::Warn(const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    std::cout << "\033[33m" // Yellow for WARNING
              << "WARNING: [" << LocalTime() << "] - " << message
              << "\033[0m"  // Reset
              << std::endl;
}
