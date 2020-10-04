#include <string>
#include <unistd.h> // pid_t


namespace PROCESS {


class Process {
public:
    explicit Process(const std::string& path);
    ~Process();

    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    bool isReadable() const;
    void closeStdin();
    void close();
private:
    pid_t pid_;
    int fdWrite_;
    int fdRead_;
    std::string path_;
};

} // PROCESS
