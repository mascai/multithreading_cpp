#pragma once

#include <string>

namespace LOG {

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};


class BaseLogger {
public:
    BaseLogger(LogLevel level);
    virtual ~BaseLogger() {};

    void debug(const std::string& s);
    void info(const std::string& s);
    void warn(const std::string& s);
    void error(const std::string& s);

    void setLevel(LogLevel level);
    LogLevel getLevel() const;

    virtual void flush() = 0;
private:
    void log(const std::string& s, LogLevel level);
    virtual void logImpl(const std::string& s) = 0;

private:
    LogLevel level_;
};





} // LOG
