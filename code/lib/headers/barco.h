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

    unsigned short posX;
    unsigned short posY;

    char nombre;

    // std::vector<std::pair<unsigned short, unsigned short>> posiciones;

    /*
    Verdadera : Horizontal
    Falsa : Vertical
    */
    bool dir;

public:
    Barco(char , unsigned short);
    void cambia_valor(unsigned short, unsigned short);
    void muestra_barco() const;
    void actualizar_vida();
    void cambiar_dir();
    unsigned short get_longitud();
    char get_nombre();
    bool get_direccion();
};

#endif // !BARCO_H
