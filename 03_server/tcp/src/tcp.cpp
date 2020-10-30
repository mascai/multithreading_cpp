#include <string>
#include <stdexcept> // runtime_error
#include <algorithm>
#include <iostream>

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "tcp.h"


namespace TCP {

static void check_error(int fd, const std::string errorMessage) {
    if (fd < 0) {
        throw std::runtime_error(errorMessage);
    }
}

Connection::Connection(const std::string& host, int port) : host_(host), port_(port)  {
    descriptor_ = ::socket(AF_INET, SOCK_STREAM, 0);
    check_error(descriptor_.getValue(), "Error in ::socket()");

    try {
        connect(host, port);
    } catch(const std::runtime_error& exception) {
        close();
        throw exception;
    }
}

Connection::Connection(Connection&& other)
    : descriptor_(std::move(other.descriptor_))
    , host_(std::move(other.host_))
    , port_(std::exchange(other.port_, -1))
    , isOpen_(std::exchange(other.isOpen_, false))
{}

Connection::Connection(Descriptor fd, const sockaddr_in& sockAddr)
    : host_(15, '\0')
    , port_(sockAddr.sin_port)
    , isOpen_(true) {

     descriptor_.setValue(std::move(fd.getValue()));
     fd.setValue(-1);

    inet_ntop(AF_INET,
        &sockAddr.sin_addr,
        host_.data(),
        static_cast<in_port_t>(host_.size())
    );
}

Connection::~Connection() {
    try {
        close();
    } catch(...) {
        std::cout << "Handled exception in ~Connection()" << std::endl;
    }
}

void Connection::connect(const std::string& host, int port) {
    if (isOpen_) {
        close();
    }
    sockaddr_in sockAddr{};
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = ::htons(port);
    sockAddr.sin_addr.s_addr = ::inet_addr(host.c_str());

    int connectionRes = ::connect(descriptor_.getValue(),
                                 reinterpret_cast<sockaddr*>(&sockAddr),
                                 sizeof(sockAddr));
    check_error(connectionRes, "Error in ::connect()");

    host_ = host;
    port_ = port_;
    isOpen_ = true;
}

void Connection::close() {
    if (descriptor_.getValue() != -1) {
        descriptor_.close();
    }
    isOpen_ = false;
}

size_t Connection::write(const void* data, size_t len) {
    if (descriptor_.getValue() != -1) {
        ssize_t numBytes = ::write(descriptor_.getValue(), data, len);
        if (numBytes < 0) {
            throw std::runtime_error("Invalid write()");
        }
        return numBytes;
    }
    throw std::runtime_error("Write descriptor is closed");
}

void Connection::writeExact(const void* data, size_t len) {
    size_t curBytes = 0;
    while (curBytes != len) {
        const void* curData = static_cast<const char*>(data) + curBytes;
        curBytes += write(curData, len - curBytes);
    }
}

size_t Connection::read(void* data, size_t len) {
    if (descriptor_.getValue() != -1) {
        ssize_t numBytes = ::read(descriptor_.getValue(), data, len);
        if (numBytes < 0) {
            throw std::runtime_error("Invalid read()");
        }
        return numBytes;
    }
    throw std::runtime_error("Read descriptor is closed");
}

void Connection::readExact(void* data, size_t len) {
    int curBytes = 0;
    while (curBytes != len) {
        void* curData = static_cast<char*>(data) + curBytes;
        curBytes += read(curData, len - curBytes);
        if (curBytes == 0) {
            throw std::runtime_error("Read 0 bytes from buffer");
        }
    }
}

void Connection::setTimeout(int numSeconds) {
    timeval timeVal{numSeconds, 0};
    if (::setsockopt(descriptor_.getValue(),
        SOL_SOCKET, // To manipulate  options at  the sockets API level
        SO_RCVTIMEO, // Receive timeout
        &timeVal,
        sizeof(timeVal)) != 0) {

        throw std::runtime_error("Error setsockopt");
    }
}


Server::Server(const std::string& host, int port, int maxConnections) {
    open(host, port, maxConnections);
    isOpen_ = true;
    setMaxConnections(maxConnections);
}

Server::~Server() {
    close();
}

void Server::open(const std::string& host, int port, int maxConnections) {
    if (isOpen_) {
        close();
    }
    descriptor_ = ::socket(AF_INET, SOCK_STREAM, 0);
    check_error(descriptor_.getValue(), "Error in socket");
    sockaddr_in sockdata{};
    sockdata.sin_family = AF_INET;
    sockdata.sin_port = ::htons(port);
    if (::inet_aton(host.c_str(), &sockdata.sin_addr) == 0) {
        close();
        throw std::runtime_error("Invalid host or port");
    }
    if (::bind(descriptor_.getValue(), reinterpret_cast<sockaddr*>(&sockdata), sizeof(sockdata)) != 0) {
        close();
        throw std::runtime_error("Error binding socket");
    }
    isOpen_ = true;
    setMaxConnections(maxConnections);
}

Connection Server::accept() {
    sockaddr_in clientAddr;
    socklen_t size = sizeof(clientAddr);

    int fd = ::accept(descriptor_.getValue(),
                      reinterpret_cast<sockaddr*>(&clientAddr),
                      &size);
    check_error(fd, "Error in accept()");
    return Connection(Descriptor(fd), clientAddr);
}

void Server::close() {
    if (descriptor_.getValue() != -1) {
        descriptor_.close();
    }
    isOpen_ = false;
}

void Server::setMaxConnections(int n) {
    if (::listen(descriptor_.getValue(), n) != 0) {
        throw std::runtime_error("Error in ::listen");
    }
}

} // TCP
