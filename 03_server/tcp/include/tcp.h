#include <string>
#include <netinet/in.h>

#include "Descriptor.h"


namespace TCP {


class Connection {
public:
    friend class Server;

    explicit Connection(const std::string& host = "127.0.0.1", int port = 8001);
    Connection(Descriptor fd, const sockaddr_in& sockAddr);
    ~Connection() noexcept;

    Connection(const Connection& other) = delete;
    Connection(Connection&& other);

    Connection operator=(const Connection& other) = delete;

    void connect(const std::string& host, int port);
    void close();
    size_t write(const void* data, size_t len);
    void writeExact(const void* data, size_t len);
    size_t read(void* data, size_t len);
    void readExact(void* data, size_t len);

    void setTimeout(int numSeconds);
    std::string getHost() const { return host_; }
    int getPort() const { return port_; }

private:
    Descriptor descriptor_;

    std::string host_;
    int port_;
    bool isOpen_ = false;
};


class Server {
public:
    Server(const std::string& host, int port, int maxConnections = 1000);
    ~Server();

    void open(const std::string& host, int port, int maxConnection);
    Connection accept();
    void close();
    void setMaxConnections(int n);

private:
    Descriptor descriptor_;
    bool isOpen_;

};

} // TCP
