#include <iostream>

#include "StdoutLogger.h"

namespace LOG {

    StdoutLogger::StdoutLogger(LogLevel level) : BaseLogger(level) {}

    void StdoutLogger::flush() {
        std::cout.flush();
    }

    void StdoutLogger::logImpl(const std::string& s) {
        std::cout << s << std::endl;
    }

} // LOG
