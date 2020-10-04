#include "process.h"
#include <iostream>


int main() {
    PROCESS::Process proc("/bin/cat");
    while (!feof(stdin)) {
        std::string temp;
        std::cin >> temp;

        proc.writeExact(temp.c_str(), temp.size());
        char* buf = new char[temp.size()];
        proc.readExact(buf, temp.size());
        std::cout << buf << std::endl;
    }
    return 0;
}
