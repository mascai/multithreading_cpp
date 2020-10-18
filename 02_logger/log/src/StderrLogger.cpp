#include <iostream>

#include "StderrLogger.h"

namespace LOG {

    StderrLogger::StderrLogger(LogLevel level) : BaseLogger(level) {}

    void StderrLogger::flush() {
        std::cout.flush();
    }

    void StderrLogger::logImpl(const std::string& s) {
        std::cerr << s << std::endl;
    }

} // LOG
