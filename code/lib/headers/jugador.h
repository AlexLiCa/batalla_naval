#ifndef JUGADOR_H
#define JUGADOR_H

// necessary includes -------->
#include <iostream>
#include <vector>
#include <limits>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <thread>
#include <fcntl.h>
#include <cstring>
#include <sys/mman.h>
#include "./tablero.h"
#include "./barco.h"

// class declaration -------->
class Jugador
{
private:
    std::vector<Barco> barcos;
    Tablero tablero_jugador;
    Tablero tablero_oponente;
    bool tablero_listo;
    bool tiene_acceso;
    std::thread hilo;
    sem_t *sem;
    int shm_fd;
    void* memory_ptr;
    void esperando_turno();
    
    struct mensaje {
        int coordenadas[2];
        char valor;
    };

public:
    Jugador();
    ~Jugador();
    void muestra_tablero(bool);
    void colocar_barco();
    
    void tirar();
    void iniciar_hilo();
    void finalizar_hilo();

    void cambia_acceso();
    bool get_tiene_acceso(); 
};

#endif // !JUGADOR_H
