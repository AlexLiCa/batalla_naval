#ifndef TABLERO_H
#define TABLERO_H

// necessary includes -------->
#include <vector>
#include <iostream>
#include <iomanip>
#include "./barco.h"

// class declaration -------->
class Tablero
{
private:
    std::vector<std::vector<char>> tablero;

public:
    Tablero(void);
    void muestra_tablero();
    void tira();
    void coloca_barco(Barco &, unsigned short, unsigned short, bool);
    bool checa_posicion(Barco &, unsigned short, unsigned short);
};

#endif // !TABLERO_H
