// necessary includes -------->
#include "../headers/barco.h"
// #include "barco.h"
using namespace std;

// functions definition -------->
Barco::Barco(unsigned short x, unsigned short y, bool dir, unsigned short longitud) : posX(x), posY(y), dir(dir), longitud(longitud) {}

// Función para imprimir la información del barco (solo para propósitos de prueba)
void Barco::muestra_barco()
{
    cout << "Posición X: " << posX << endl;
    cout << "Posición Y: " << posY << endl;
    cout << "Longitud: " << longitud << endl;
    cout << "direccion: " << dir << endl;
}

unsigned short Barco::get_longitud()
{
    return this->longitud;
}
bool Barco::get_direccion()
{
    return this->dir;
}