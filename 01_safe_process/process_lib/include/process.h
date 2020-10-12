#include <string>
#include <unistd.h> // pid_t


namespace PROCESS {


class Descriptor {
public:
    Descriptor(int fd);
    ~Descriptor(); // after the destructor, ownership is transferred to the containing class
    int getFd() const;
    void operator=(int fd);
private:
    int fd_;
};

class Process {
public:
    using PipeType = int[2];
    explicit Process(const std::string& path);
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);
    void closeStdin();
    void close();

    bool is_readable() const;
private:
    void safe_pipe(PipeType& fd);
private:
    pid_t pid_;
    Descriptor fdWrite_ = -1;
    Descriptor fdRead_ = -1;
    std::string path_;
    bool readable_ = false;
};

} // PROCESS
