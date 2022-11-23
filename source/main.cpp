
#include "utils/logger.h"
#include "settings/settings.h"

#include <iostream>
#include <format>

#include <boost/program_options.hpp>

namespace {
const uint32_t BUILD{ 1 };
const uint32_t MINOR{ 0 };
const uint32_t MAJOR{ 0 };

const std::string default_host{ "localhost" };
const std::string default_port{ "40400" };

const std::string tcp_group{ "tcp_settings" };
const std::string tcp_addr_param{ "ip_addr" };
const std::string tcp_port_param{ "ip_port" };
}

static void PrintProgramOptions(int argc, char* argv[]) {

    using namespace boost::program_options;

    options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        desc.print(std::cout);
        return;
    }
}

static void PrintApplicationVersion() {

    std::stringstream version{};
    version << "Application build " << "v." << MAJOR << "." << MINOR << "." << BUILD << " from " << __DATE__ << " " << __TIME__;
    Utils::Logger::GetInstance().write(version.str());
}

int main(int argc, char* argv[]) {

    try {
        // print main application info and initialize begin settings
        PrintApplicationVersion();
        PrintProgramOptions(argc, argv);

        Settings::GlobalSettings::GetInstance().SetVariable(tcp_group, tcp_addr_param, default_host);
        Settings::GlobalSettings::GetInstance().SetVariable(tcp_group, tcp_port_param, default_port);

        { // test read global variables
            using namespace Utils;
            using namespace Settings;

            Logger::GetInstance().write("Default IP address: " + GlobalSettings::GetInstance().GetVariable(tcp_group, tcp_addr_param), LogLevel::test);
            Logger::GetInstance().write("Default IP port: " + GlobalSettings::GetInstance().GetVariable(tcp_group, tcp_port_param), LogLevel::test);
        }

        // other work
    } 
    catch(const std::exception & ex) {
        std::cout << "Exception cauht: " << ex.what() << "\n";
    }
  return EXIT_SUCCESS;
}