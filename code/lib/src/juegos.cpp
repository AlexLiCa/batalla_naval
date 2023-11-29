// Juegos.cpp

#include "../headers/juegos.h"

Juegos::Juegos()
{
    // Constructor, si es necesario
}

Juegos::~Juegos()
{
    for (auto &pair : semaphores_)
    {
        sem_close(pair.second);

        // Obtener el nombre del semáforo
        std::string semName = pair.first;

        // Eliminar el nombre del semáforo del sistema de archivos
        if (sem_unlink(semName.c_str()) == 0)
        {
            std::cout << "Se ha eliminado el nombre del semaforo '" << semName << "' del sistema de archivos." << std::endl;
        }
        else
        {
            std::cerr << "Error al intentar eliminar el nombre del semaforo '" << semName << "'." << std::endl;
        }
    }
}

bool Juegos::createSemaphore(const std::string &name)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (semaphores_.count(name) == 0)
    {
        sem_t *sem = sem_open(name.c_str(), O_CREAT, 0660, 1);
        if (sem == SEM_FAILED)
        {
            std::cout << "Error al crear el semaforo '" << name << "'." << std::endl;
            return false;
        }
        semaphores_[name] = sem;
        std::cout << "Se ha creado el semaforo '" << name << "'." << std::endl;
        return true;
    }
    else
    {
        std::cout << "El nombre del semaforo '" << name << "' ya está ocupado. No se puede crear." << std::endl;
        return false;
    }
}

bool Juegos::enterSemaphore(const std::string &name)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (semaphores_.count(name) > 0)
    {
        std::cout << "Intentando entrar al semaforo '" << name << "'." << std::endl;
        if (sem_trywait(semaphores_[name]) == 0)
        {
            std::cout << "Bienvenido al semaforo '" << name << "'." << std::endl;
            return true;
        }
        else
        {
            std::cout << "El semaforo '" << name << "' ya está ocupado. No se puede entrar." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "El semaforo '" << name << "' no existe. No se puede entrar." << std::endl;
        return false;
    }
}

