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
    int fifo_fd;
    bool tiene_acceso;
    std::thread hilo;
    sem_t *sem;
    int shm_fd;
    void *memory_ptr;
    void esperando_turno(short &);
    std::string nombre;
    std::string sem_name;

    struct mensaje
    {
        int coordenadas[2];
        char valor;
    };

public:
    Jugador(std::string);
    ~Jugador();
    void muestra_tablero(bool);
    void colocar_barco();
    void resumen_barcos();
    void posiciones_barcos();

    bool aun_hay_barcos();

    void tirar(short &);
    void iniciar_hilo(short &);
    void finalizar_hilo(bool);

    void cambia_acceso();
    bool get_tiene_acceso();

    void limpiar_archivo(const char *);
    void escribirEnArchivo(mensaje);

    bool get_tablero_listo();

    void rage_quit(short &);
};

#endif // !JUGADOR_H
