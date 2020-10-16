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
    ~BaseLogger() = default;

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


/* TODO: singleton
class Logger : public BaseLogger {
public:
    static Logger& get_instance();
    std::shared_ptr<BaseLogger> get_global_logger() const;
    void set_global_logger(std::shared_ptr<BaseLogger>r logger);
private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger& other) = delete;
    Logger& operator=(const Logger& other) = delete;
private:
    std::shared_ptr<BaseLogger> global_logger;
};*/

} // LOG
