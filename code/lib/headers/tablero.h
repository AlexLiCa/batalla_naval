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
    void tira();

    /// @brief Coloca un Barco
    /// @param barco Referencia al barco que se quiere colocar
    /// @param x1 Posición Inicial en x
    /// @param y1 Posición Inicial en y
    /// @return Mensajes de error en caso de que la colocación falle

    void coloca_barco(Barco &, unsigned short , unsigned short );

    /*Funcion para verificar si es posible agregar un barco de longitud n
    con en una direccion iniciando en una posicion (x,y) del tablero 
    
    Regresa:
        Un bool dependiendo de si es posible agregar el barco en la posicion indicada*/
    bool checa_posicion(unsigned short , unsigned short , unsigned short  ,bool );
};

#endif // !TABLERO_H
