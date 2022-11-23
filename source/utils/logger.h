
#pragma once

#include "config.h"

#include <memory>
#include <string>
#include <iostream>
#include <mutex>
#include <chrono>
#include <typeinfo>

namespace Utils {

enum class LogLevel
{   
    test,
    debug,
    trace,
    warning,
    error,
    fatal
};

namespace {
const LogLevel compiledLevel = LogLevel::trace;
}

class Logger
{
public:

    Logger(Logger&) = delete;
    Logger& operator=(Logger&) = delete;

    static const Logger& GetInstance() {
        static std::unique_ptr<Logger> log(new Logger());
        return *log;
    }

    void write(std::string&& s, LogLevel level = LogLevel::trace) const {
        std::lock_guard<std::mutex> lk(m);

        if (compiledLevel > level) {
            return;
        }

        // print data according to log level
        std::cout << "[" << getTimestamp() << "] " << s << "\n";
    }

    ~Logger() {
        write("Construct " + className + " object", Utils::LogLevel::debug);
    }

private:

    Logger() {
        write("Construct " + className + " object", Utils::LogLevel::debug);
    }

    inline std::chrono::system_clock::time_point getTimestamp() const {
        return std::chrono::system_clock::now();
    };

private:

    std::string className = typeid(Logger).name();
    mutable std::mutex m;
};
}