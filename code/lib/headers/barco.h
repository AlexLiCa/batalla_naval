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

    std::vector<std::pair<unsigned short, unsigned short>> posiciones;

    /*
    Verdadera : Horizontal
    Falsa : Vertical
    */
    bool dir;
    bool colocado;

public:
    Barco(char, unsigned short);
    void checa_coordenadas(unsigned short, unsigned short);
    void muestra_barco() const;
    void actualizar_vida();
    void cambiar_dir();
    unsigned short get_longitud();
    char get_nombre();
    bool get_direccion();
    void agrega_coordenada(unsigned short, unsigned short);
    bool get_colocado();
};

#endif // !BARCO_H
