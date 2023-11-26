// necessary includes -------->
#include "../headers/tablero.h"

using namespace std;
// functions definition -------->
Tablero::Tablero()
{
    this->tablero = {
        {'D', 'D', 'D', 'D', '0', '0', '0', '0', '0', '0'},
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
    /*Horizontal*/
    if (direccion)
    {
        for (unsigned short i = x1; i < x1 + barco.get_longitud(); i++)
        {
            // cout << direccion << endl;
            tablero[i][y1] = barco.get_nombre();
        }
    }
    /*Vertical*/
    else
    {
        for (unsigned short i = y1; i < y1 + barco.get_longitud(); i++)
        {
            tablero[x1][i] = barco.get_nombre();
        }
    }
}

bool Tablero::checa_posicion(unsigned short x, unsigned short y, unsigned short longitud, bool direccion)
{
    bool valida = true;
    if (direccion) // Si la dirección es verdadera (1), horizontal
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = x; i < x + longitud; ++i)
        {

            if (i >= 10 || i < 0)
            {
                valida = false;
                break;
            }
            else if (tablero[i][y] != '0')
            {
                valida = false;
                break;
            }
        }
    }
    else // Si la dirección es falsa (0), vertical
    {
        // Verificar si las posiciones están dentro de los límites y son '0'
        for (unsigned short i = y; i < y + longitud; ++i)
        {
            if (i >= 10 || i < 0)
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

unsigned short Tablero::barcos_restantes()
{
    int total = 0;

    // Recorre la matriz y suma la cantidad de cada caracter
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (tablero[i][j] == 'A' || tablero[i][j] == 'B' || tablero[i][j] == 'C' || tablero[i][j] == 'D')
            {
                total++;
            }
        }
    }
    return total;
}

unsigned short Tablero::tira(short x, short y)
{
    unsigned short vidas = -1;
    if (tablero[x][y] == 'A' || tablero[x][y] == 'B' || tablero[x][y] == 'C' || tablero[x][y] == 'D')
    {
        vidas = barcos_restantes();
        cout << "Vidas restantes: " << vidas << endl;
        if (vidas > 0)
        {
            tablero[x][y] = 'E';
            vidas = 1;
        }
        else if (vidas == 0)
        {
            vidas = 2;
        }
    }
    else if (tablero[x][y] == 'X' || tablero[x][y] == 'E')
    {
        vidas = 3;
    }
    else
    {
        tablero[x][y] = 'X'; 
        vidas = 0;
    }
    return vidas;
}
