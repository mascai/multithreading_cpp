#include <string>
#include <unistd.h> // pid_t
#include <stdexcept> // std::runtime_error

#include "../include/process.h"

namespace PROCESS {


Process::Process(const std::string& path) : path_(path) {

    int p1[2], p2[2];
    safe_pipe(p1);
    safe_pipe(p2);

    pid_ = fork();
    if (pid_ == 0) { // child process
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        ::close(p1[0]);
        ::close(p1[1]);
        ::close(p2[0]);
        ::close(p2[1]);

        if (execl(path_.c_str(), path_.c_str(), nullptr) < 0) {
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
    if (fdWrite_ != -1) {
        ssize_t numBytes = ::write(fdWrite_, data, len);
        if (numBytes < 0) {
            throw std::runtime_error("Invalid write()");
        }
        return numBytes;
    }
    throw std::runtime_error("Write descriptor is closed");

}
void Process::writeExact(const void* data, size_t len) {
    size_t curBytes = 0;
    while (curBytes != len) {
        const void* curData = static_cast<const char*>(data) + curBytes;
        curBytes += write(curData, len - curBytes);
    }
}

size_t Process::read(void* data, size_t len) {
    if (fdRead_ != -1) {
        ssize_t numBytes = ::read(fdRead_, data, len);
        if (numBytes < 0) {
            throw std::runtime_error("Invalid read()");
        }
        return numBytes;
    }
    throw std::runtime_error("Read descriptor is closed");
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
    fdWrite_ = -1;
}

void Process::close() {
    ::close(fdRead_);
    ::close(fdWrite_);
    fdWrite_ = -1;
    fdRead_ = -1;
}

void Process::safe_pipe(PipeType& fd) {
    if (pipe(fd) < 0) {
        throw std::runtime_error("Invalid pipe");
    }
}

} // PROCESS
