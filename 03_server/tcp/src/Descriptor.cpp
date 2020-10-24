#include <unistd.h>

#include "Descriptor.h"

namespace TCP {

Descriptor::Descriptor(int fd) : fd_(fd) {}

Descriptor::~Descriptor() {
    close();
}

Descriptor::Descriptor(Descriptor&& other) {
    fd_ = other.fd_;
    other.fd_ = -1;
}

int Descriptor::getValue() const {
    return fd_;
}

int Descriptor::setValue(int fd) {
    fd_ = fd;
}

Descriptor& Descriptor::operator=(int fd) {
    fd_ = fd;
}

void Descriptor::close() {
    ::close(fd_);
    fd_ = -1;
}

} // TCP
