
#include "settings.h"

#include <memory>
#include <map>

#include <boost/lexical_cast.hpp>

namespace Settings {

namespace {
std::map<std::string, std::map<std::string, std::string>> globalVariables;
}

void GlobalSettings::SetVariable(const std::string& group, const std::string& parameter, const std::string& value) {
    if (!globalVariables.contains(group)) {
        globalVariables.insert({ group, {  } });
        globalVariables[group].insert({ parameter, value } );
        return;
    }

    if (!globalVariables[group].contains(parameter)) {
        globalVariables[group][parameter] = value;
        return;
    }

    globalVariables[group][parameter] = value;
}

const std::string& GlobalSettings::GetVariable(const std::string& group, const std::string& parameter) {

    if (!globalVariables.contains(group) || !globalVariables[group].contains(parameter)) {
        throw std::out_of_range("there is no group or parameter");
    }
    return globalVariables[group][parameter];
}

}