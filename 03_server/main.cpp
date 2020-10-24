#include <string>
#include <iostream>

#include "tcp.h"

using namespace std;


int main(int argc, char* argv[]) {
    TCP::Server server("127.0.0.1", 9005, 10);
    TCP::Connection conn(server.accept());

    std::cout << "Connection accepted: " <<
        conn.getHost() << ':' << conn.getPort() << std::endl;

    std::string msg = "Test buffer\n";
    while (1) {
        try {
            conn.readExact(msg.data(), msg.size());
        }
        catch(const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }

        conn.writeExact(msg.data(), msg.size());
        std::cout << "writeExact " << msg.size() << " bytes (including '\\n'):\n" << msg << std::endl;
    }

    return 0;
}
