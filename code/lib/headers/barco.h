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

    std::vector<std::pair<unsigned short, unsigned short>> posiciones;

    bool dir;

public:
    Barco(void);
    void actualizar_vida();
    void cambiar_dir();
};

#endif // !BARCO_H
