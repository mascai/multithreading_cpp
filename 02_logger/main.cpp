#include "log/include/FileLogger.h"


int main() {
    LOG::FileLogger fileLogger("file.txt", LOG::LogLevel::INFO);
    fileLogger.info("example text");

}
