#include <unistd.h>

#include "Descriptor.h"

namespace TCP {

Descriptor::Descriptor(int fd) : fd_(fd) {}

Descriptor::~Descriptor() {
    close();
}

Descriptor::Descriptor(Descriptor&& other) {
    if (fd_ != other.fd_) {
        ::close(fd_);
        fd_ = other.fd_;
    }

}

int Descriptor::getValue() const {
    return fd_;
}

void Descriptor::setValue(int fd) {
    if (fd_ != fd) {
        ::close(fd_);
        fd_ = fd;
    }
}

Descriptor& Descriptor::operator=(int fd) {
    setValue(fd);
    return *this;
}

void Descriptor::close() {
    ::close(fd_);
    fd_ = -1;
}

} // TCP
