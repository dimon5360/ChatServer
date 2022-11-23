
#pragma once

#include "logger.h"

#include <string>
#include <memory>

namespace Settings
{
class GlobalSettings
{
public:

    GlobalSettings(const GlobalSettings&) = delete;
    GlobalSettings& operator=(const GlobalSettings&) = delete;

    static GlobalSettings& GetInstance() {
        static std::unique_ptr<GlobalSettings> settings(new GlobalSettings());
        return *settings;
    }

    void SetVariable(const std::string& group, const std::string& parameter, const std::string& value);

    const std::string& GetVariable(const std::string& group, const std::string& parameter);

    ~GlobalSettings() {
        Utils::Logger::GetInstance().write("Destruct " + className + " object", Utils::LogLevel::debug);
    }

private:

    GlobalSettings() {
        Utils::Logger::GetInstance().write("Construct " + className + " object", Utils::LogLevel::debug);
    }

private:

    std::string className = typeid(GlobalSettings).name();
};
}