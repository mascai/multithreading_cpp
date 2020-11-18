#include <iostream>

#include "SharedMap.h"

using namespace std;

int main() {
    SHMEM::SharedMap<int, int> m(8, 8);
    //m.insert({1, 10});

}
