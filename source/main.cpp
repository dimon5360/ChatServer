/**
 *
 */

#include "utils/logger.h"

#include <iostream>

#include <boost/program_options.hpp>

namespace {
const uint32_t BUILD = 1;
const uint32_t MINOR = 0;
const uint32_t MAJOR = 0;
}

static void PrintApplicationVersion() {
    std::stringstream version{};
    version << "Application build " << "v." << MAJOR << "." << MINOR << "." << BUILD << " from " << __DATE__ << " " << __TIME__;
    Utils::LogUtil::GetInstance().write(version.str());
}

int main(int argc, char* argv[]) {

    boost::program_options::options_description desc("Allowed options");
    try {
        PrintApplicationVersion();
        std::ignore = argc;
        std::ignore = argv;
    } 
    catch(const std::exception & ex) {
        std::cout << "Exception cauht: " << ex.what() << "\n";
    }
  return EXIT_SUCCESS;
}