#include <fstream>

#include "log.h"


namespace LOG {

class FileLogger : public BaseLogger {
public:
    FileLogger(const std::string& fileName, LogLevel level);
    void flush() override;
private:
    void logImpl(const std::string& log_msg) override;
private:
    std::ofstream stream_;
};

} // LOG
