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
    std::vector<std::vector<char> > tablero;

public:
    Tablero(void);
    void muestra_tablero();

    /// @brief Coloca un Barco
    /// @param barco Referencia al barco que se quiere colocar
    /// @param x1 Posición Inicial en x
    /// @param y1 Posición Inicial en y
    /// @return Mensajes de error en caso de que la colocación falle


    void coloca_barco(Barco &, unsigned short , unsigned short, bool );


    /*Funcion para tirar en el tablero de un jugador.
        Regresa:
            0: Si no le dio a un barco - Se cambiara el valor de la coordenada a "X" 
            1: Si le dio un barco      - Se cambiara el valor de la coordenada a "E"
            2: Si le dio a un barco y no quedan mas barcos
            3: Si la coordenada indicada ya tenia una "X" o una "E" */
    unsigned short tira(short, short);


    /*Funcion para verificar si es posible agregar un barco de longitud n
    con en una direccion iniciando en una posicion (x,y) del tablero 
    
    Regresa:
        Un bool dependiendo de si es posible agregar el barco en la posicion indicada*/
    bool checa_posicion(unsigned short , unsigned short , unsigned short  , bool );


    /*Funcion para contar la cantidad de veces que aparecen los caracteres :
        "A", "B", "C" y "D" en el tablero, regresa un unsigned short*/
    unsigned short barcos_restantes();
};

#endif // !TABLERO_H
