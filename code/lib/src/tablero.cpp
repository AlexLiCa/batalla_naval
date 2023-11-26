// necessary includes -------->
#include "../headers/tablero.h"

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

void Tablero::coloca_barco(Barco &barco, unsigned short x1, unsigned short y1, bool direccion)
{
    unsigned short pos_inicial = direccion ? y1 : x1;

    for (unsigned short i = pos_inicial; i < pos_inicial + barco.get_longitud(); i++)
    {
        if(direccion)
        {
            tablero[i][x1] = barco.get_nombre();
        }
        else 
        {
            tablero[y1][i] = barco.get_nombre();
        }
    }
}

bool Tablero::checa_posicion(unsigned short x, unsigned short y, unsigned short longitud, bool direccion)
{
    unsigned short pos_inicial = direccion ? y : x;

    unsigned short pos_final = pos_inicial + longitud;

    if(pos_final >= 10){
        return false;
    }

    // Verificar si las posiciones están dentro de los límites y son '0'
    for (unsigned short i = pos_inicial; i < pos_final; ++i)
    {
        char valor_actual = direccion ? tablero[x][i] : tablero[i][y];
        
        if (valor_actual != '0')
        {
            return false;
        }
    }

    // Si se llega aquí, significa que las posiciones están disponibles
    return true;
}

void Tablero::muestra_tablero()
{
    for (short i = 0; i < 5; i++)
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
            char valor_a_imprimir = this->tablero[i][j] != '0' ? this->tablero[i][j] : ' ';
            
            std::cout << valor_a_imprimir << " | ";
        }
        std::cout << std::endl;
        std::cout << separador << std::endl;
    }
}

void Tablero::tira()
{
}
