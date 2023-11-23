#ifndef BARCO_H
#define BARCO_H

// necessary includes -------->
#include <vector>
#include <iostream>

// class declaration -------->
class Barco
{
private:
    unsigned short longitud;

    unsigned short vida;

    unsigned short x;  
    unsigned short y;

    //std::vector<std::pair<unsigned short, unsigned short>> posiciones;

    /*
    Verdadera : Horizontal 
    Falsa : Vertical
    */
    bool dir;

public:
    Barco(void);
    void actualizar_vida();
    void cambiar_dir();
    unsigned short get_longitud();
    bool get_direccion();
};

#endif // !BARCO_H
