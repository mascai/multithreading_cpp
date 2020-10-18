#include "log.h"


namespace LOG {

BaseLogger::BaseLogger(LogLevel level) : level_(level) {}

void BaseLogger::debug(const std::string& s) {
    log(s, LogLevel::DEBUG);
}

void BaseLogger::info(const std::string& s) {
    log(s, LogLevel::INFO);
}

void BaseLogger::warn(const std::string& s) {
    log(s, LogLevel::WARN);
}

void BaseLogger::error(const std::string& s) {
    log(s, LogLevel::ERROR);
}

void BaseLogger::setLevel(LogLevel level) {
    level_ = level;
}

LogLevel BaseLogger::getLevel() const {
    return level_;
}

void BaseLogger::log(const std::string& s, LogLevel level) {
    if (level >= level_) {
        logImpl(s);
    }
}

} // LOG
