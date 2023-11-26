// necessary includes -------->
#include "../headers/barco.h"

// functions definition -------->
Barco::Barco(char nombre, unsigned short longitud) : nombre(nombre), longitud(longitud) {}

// Función para imprimir la información del barco (solo para propósitos de prueba)
void Barco::muestra_barco() const
{
    std::cout  << nombre <<  "--" << longitud << std::endl;
}

unsigned short Barco::get_longitud()
{
    return this->longitud;
}
bool Barco::get_direccion()
{
    return this->dir;
}

char Barco::get_nombre(){
    return this->nombre;
}