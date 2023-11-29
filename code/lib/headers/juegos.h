// Juegos.h

#ifndef SEMAPHORE_MANAGER_H
#define SEMAPHORE_MANAGER_H

#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <map>
#include <mutex>

class Juegos
{
public:
    Juegos();
    ~Juegos();

    bool createSemaphore(const std::string &name);
    bool enterSemaphore(const std::string &name);

private:
    std::map<std::string, sem_t *> semaphores_;
    std::mutex mutex_;
};

#endif // SEMAPHORE_MANAGER_H
