#pragma once

#include <fstream>

#include "log.h"


namespace LOG {

class StderrLogger : public BaseLogger {
public:
    StderrLogger(LogLevel level);
    virtual ~StderrLogger() {} // define destructor to eliminate "undefined reference to `vtable for LOG::BaseLogger'"
    void flush() override;
private:
    void logImpl(const std::string& s) override;
};

} // LOG
