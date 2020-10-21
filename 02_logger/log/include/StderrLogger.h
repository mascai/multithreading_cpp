#include <fstream>

#include "log.h"


namespace LOG {

class StderrLogger : public BaseLogger {
public:
    StderrLogger(LogLevel level);
    void flush() override;
private:
    void logImpl(const std::string& s) override;
};

} // LOG
