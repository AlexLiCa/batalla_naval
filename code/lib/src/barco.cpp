// necessary includes -------->
#include "../headers/barco.h"
#include "barco.h"
// #include "barco.h"

// functions definition -------->
Barco::Barco(void)
{
}

unsigned short Barco::get_longitud()
{
    return this->longitud;
}
bool Barco::get_direccion()
{
    return this->dir;
}