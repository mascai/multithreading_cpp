#include <cstring> // strerror

#include "Exception.h"

namespace TCP {

Exception::Exception() : std::runtime_error("") {}

Exception::Exception(const std::string& msg) : std::runtime_error(msg) {
    msg_ = msg;
}

const char* Exception::what() const noexcept {
    return msg_.c_str();
}


} // TCP
