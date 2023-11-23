// necessary includes -------->
#include "../headers/tablero.h"
#include "tablero.h"

// functions definition -------->
Tablero::Tablero()
{
    this->tablero = {
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    };
}

void Tablero::muestra_tablero()
{
    for (short i = 0; i < 100; i++)
    {
        std::cout << "\n";
    }

    std::string separador = "  +---------------------------------------+";

    std::cout << "  ";
    for (short i = 0; i < 10; i++)
    {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    std::cout << separador << std::endl;
    for (short int i = 0; i < this->tablero.size(); i++)
    {
        std::cout << i << " | ";
        for (short int j = 0; j < this->tablero[i].size(); j++)
        {
            std::cout << this->tablero[i][j] << " | ";
        }
        std::cout << std::endl;
        std::cout << separador << std::endl;
    }
}

void Tablero::tira()
{
}

void Tablero::coloca_barco(Barco &barco, unsigned short x1, unsigned short y1)
{
    if (barco.get_direccion())
    {
        for (unsigned short i = y1; i < barco.get_longitud(); i++)
        {
        }
    }
    else
    {
        for (unsigned short i = x1; i < barco.get_longitud(); i++)
        {
        }
    }
}