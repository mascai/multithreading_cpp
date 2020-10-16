#include "../include/FileLogger.h"


namespace LOG {

    FileLogger::FileLogger(const std::string& fileName, LogLevel level)
        : BaseLogger(level)
        , stream_(fileName)
    {}

    void FileLogger::flush() {
        stream_.flush();
    }

    void FileLogger::logImpl(const std::string& log_msg) {
        stream_ << log_msg << std::endl;
    }

}
