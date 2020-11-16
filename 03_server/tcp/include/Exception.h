#include <stdexcept>
#include <string>


namespace TCP {

class Exception : public std::runtime_error {
public:
    Exception();
    explicit Exception(const std::string& msg);
    virtual ~Exception() = default; // virtual in case of inheritance

    const char* what() const noexcept override;
private:
    std::string msg_;
};

} // TCP
