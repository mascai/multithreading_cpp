#include <string>
#include <fstream>
#include <iostream>

#include "log.h"
#include "FileLogger.h"
#include "StdoutLogger.h"
#include "StderrLogger.h"


void FileLoggerTest() {
    const std::string fileName = "file.txt";
    const std::string expected = "example text";
    LOG::FileLogger fileLogger(fileName, LOG::LogLevel::INFO);
    fileLogger.info(expected);

    std::ifstream fs(fileName);
    std::string result((std::istreambuf_iterator<char>(fs)),
                        std::istreambuf_iterator<char>());
    if (result == expected + '\n') {
        std::cout << "FileLoggerTest: OK" << std::endl;
    } else {
        std::cout << "FileLoggerTest: ERROR" << std::endl;
        std::cout << result << " != " << expected << std::endl;
    }

}

void StdoutLogger() {
    const std::string expected = "example text";
    LOG::StdoutLogger outLogger(LOG::LogLevel::WARN);
    outLogger.warn("StdoutLoggerTest: OK");
}

void StderrLogger() {
    const std::string expected = "example text";
    LOG::StderrLogger outLogger(LOG::LogLevel::ERROR);
    outLogger.error("StderrLoggerTest: OK");
}

int main() {
    FileLoggerTest();
    StdoutLogger();
    StderrLogger();
}
