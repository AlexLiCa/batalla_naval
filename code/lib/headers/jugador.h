#ifndef JUGADOR_H
#define JUGADOR_H

// necessary includes -------->
#include <iostream>
#include <vector>
#include <limits>
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

public:
    Jugador(void);
    void muestra_tablero(bool);
    void colocar_barco();
    void tirar();
};

#endif // !JUGADOR_H
