/**
 *
 */

#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <mutex>
#include <chrono>

namespace Utils {

enum class LogLevel
{   
    trace,
    debug,
    warning,
    error,
    fatal
};

class LogUtil
{
public:

    LogUtil(LogUtil&) = delete;
    LogUtil& operator=(LogUtil&) = delete;

    ~LogUtil()
    {
        std::cout << "Destruct LogUtil object" << "\n";
    }

    static LogUtil& GetInstance()
    {
        static std::unique_ptr<LogUtil> log(new LogUtil());
        return *log;
    }

    void write(std::string&& s, LogLevel level = LogLevel::trace) const
    {
        std::lock_guard<std::mutex> lk(m);
        std::cout << "[" << getTimestamp() << "] " << s << "\n";
    }

private:

    LogUtil()
    {
        std::cout << "Construct LogUtil object" << "\n";
    }

    inline std::chrono::system_clock::time_point getTimestamp() const {
        return std::chrono::system_clock::now();
    };

private:

    mutable std::mutex m;
};
}