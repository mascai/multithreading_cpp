#pragma once

#include <semaphore.h> // sem_t
#include <stdexcept> // runtime_error
#include <string>
#include <iostream>


namespace SHMEM {

static void check(int num) {
    if(num == -1) {
        throw std::runtime_error(std::strerror(errno));
    }
}


class Semaphore {
public:
    Semaphore(size_t initialValue=1) {
        check(::sem_init(&sem_,
                         1, /*  If  pshared  is nonzero, then the semaphore is shared between processes */
                         initialValue));
    }
    ~Semaphore() {
        try {
            semDestroy();
        } catch(...) {
            std::cout << "Handled exception in ~Semaphore()" << std::endl;
        }
    }

    void semWait() {
        check(::sem_wait(&sem_));
    }

    void semPost() {
        check(::sem_post(&sem_));
    }

    void semDestroy() {
        check(::sem_destroy(&sem_));
    }
private:
    sem_t sem_;
};

class LockGuard {
public:
    explicit LockGuard(Semaphore& sem) : sem_(sem) {
        sem_.semWait(); // lock a critical section
    }
    ~LockGuard();
    void semPost();
    void semWait();
    void semDestroy();

private:
    Semaphore& sem_;
};


} // SHMEM
