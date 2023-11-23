// necessary includes -------->
#include "./headers/tablero.h"


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

bool Tablero::checa_posicion(unsigned short x, unsigned short y, unsigned short longitud, bool direccion)
{
    if (direccion) // Si la dirección es verdadera, horizontal
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = y; i < y + longitud; ++i)
        {
            if (i >= 10 || i < 0 || tablero[x][i] != '0')
                return false;
                break;
        }
    }
    else // Si la dirección es falsa, vertical
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = x; i < x + longitud; ++i)
        {
            if (i >= 10 || tablero[i][y] != '0')
                return false;
                break;
        }
    }

    // Si se llega aquí, significa que las posiciones están disponibles
    return true;
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
    /*Horizontal*/
    if (barco.get_direccion())
    {
        for (unsigned short i = y1; i < barco.get_longitud(); i++)
        {
        }
    }
    /*Vertical*/
    else
    {
        for (unsigned short i = x1; i < barco.get_longitud(); i++)
        {
        }
    }
}