#include "process.h"

#include <string>
#include <unistd.h> // pid_t
#include <stdexcept> // std::runtime_error


namespace PROCESS {


Process::Process(const std::string& path) : path_(path) {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2);

    pid_ = fork();
    if (pid_ == 0) { // child process
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        ::close(p1[0]);
        ::close(p1[1]);
        ::close(p2[0]);
        ::close(p2[1]);

        if (execl(path_.c_str(), path_.c_str(), NULL) < 0) {
            throw std::runtime_error("Invalid execl()");
        }
    }
    if (pid_ > 0) { // parent process
        fdWrite_ = p1[1];
        fdRead_ = p2[0];

        ::close(p1[0]);
        ::close(p2[1]);
    }
    if (pid_ < 0) {
      throw std::runtime_error("Invalid fork()");
    }
}

Process::~Process() {
    close();
}

size_t Process::write(const void* data, size_t len) {
    int numBytes = ::write(fdWrite_, data, len);
    if (numBytes < 0) {
        throw std::runtime_error("Invalid write()");
    }
    return numBytes;

}
void Process::writeExact(const void* data, size_t len) {
    int curBytes = 0;
    while (curBytes != len) {
        const void* curData = static_cast<const char*>(data) + curBytes;
        curBytes += write(curData, len - curBytes);
    }
}

size_t Process::read(void* data, size_t len) {
    int numBytes = ::read(fdRead_, data, len);
    if (numBytes < 0) {
        throw std::runtime_error("Invalid read()");
    }
    return numBytes;
}

void Process::readExact(void* data, size_t len) {
    int curBytes = 0;
    while (curBytes != len) {
        void* curData = static_cast<char*>(data) + curBytes;
        curBytes += read(curData, len - curBytes);
    }

}

void Process::closeStdin() {
    ::close(fdWrite_);
}

void Process::close() {
    ::close(fdRead_);
    ::close(fdWrite_);
}

} // PROCESS


