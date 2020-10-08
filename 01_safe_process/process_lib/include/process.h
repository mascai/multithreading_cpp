#include <string>
#include <unistd.h> // pid_t


namespace PROCESS {


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
private:
    void safe_pipe(PipeType& fd);
private:
    pid_t pid_;
    int fdWrite_ = -1;
    int fdRead_ = -1;
    std::string path_;
};

} // PROCESS
