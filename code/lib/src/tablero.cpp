// necessary includes -------->
#include "../headers/tablero.h"

using namespace std;
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
    bool valida = true;
    if (direccion) // Si la dirección es verdadera, horizontal
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = x; i < x + longitud; ++i)
        {

            if (i >= 10 || i < 0 )
            {
                valida = false;
                break;
            }
            else if (tablero[i][y] != '0'){
                valida = false;
                break;
            }
        }
    }
    else // Si la dirección es falsa, vertical
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = y; i < y + longitud; ++i)
        {
            if (i >= 10 || i < 0 )
            {
                valida = false;
                break;
            }
            else if (tablero[x][i] != '0')
            {
                valida = false;
                break;
            }
        }
    }

    // Si se llega aquí, significa que las posiciones están disponibles
    return valida;
}

void Tablero::muestra_tablero()
{
    for (short i = 0; i < 5; i++)
    {
        cout << "\n";
    }

    string separador = "  +---------------------------------------+";

    cout << "  ";
    for (short i = 0; i < 10; i++)
    {
        cout << setw(3) << i << " ";
    }
    cout << endl;
    cout << separador << endl;
    for (short int i = 0; i < this->tablero.size(); i++)
    {
        cout << i << " | ";
        for (short int j = 0; j < this->tablero[i].size(); j++)
        {
            cout << this->tablero[i][j] << " | ";
        }
        cout << endl;
        cout << separador << endl;
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