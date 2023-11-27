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
#include "./monitor.h"
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
    int fifo_fd;
    bool tiene_acceso;
    std::thread hilo;

public:
    Jugador(sem_t &, int);
    void muestra_tablero(bool);
    void colocar_barco();
    void tirar();
    
    void cambia_acceso();
    bool get_tiene_acceso(); 
};

#endif // !JUGADOR_H
