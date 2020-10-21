#include <fstream>

#include "log.h"


namespace LOG {

class StdoutLogger : public BaseLogger {
public:
    StdoutLogger(LogLevel level);
    void flush() override;
private:
    void logImpl(const std::string& s) override;
};

} // LOG
