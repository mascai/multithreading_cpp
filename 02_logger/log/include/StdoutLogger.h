#pragma once

#include <fstream>

#include "log.h"


namespace LOG {

class StdoutLogger : public BaseLogger {
public:
    StdoutLogger(LogLevel level);
    virtual ~StdoutLogger() {} // define destructor to eliminate "undefined reference to `vtable for LOG::BaseLogger'"
    void flush() override;
private:
    void logImpl(const std::string& s) override;
};

} // LOG
