#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>

class Logger {
public:
    static void Log(const std::string& message);
    static void Err(const std::string& message);
    static void Warn(const std::string& message);

private:
    static std::string LocalTime();
    static std::mutex logMutex; // To ensure thread safety
};

#endif

