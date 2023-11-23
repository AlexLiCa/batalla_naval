#include <iostream>
#include <vector>
#include <limits>
#include "lib/headers/tablero.h"
#include "lib/headers/barco.h"

using namespace std;

/*Funcion que le pide al usuario que ingrese coordenadas, si las coordenadas no 
    son por numeros regresa una tupla con dos "-1"*/
tuple<short, short> capturar_coordenadas()
{
    short x, y;

    cout << "Ingresa dos valores (x y): ";
    if (!(cin >> x >> y))
    {
        // Si la entrada no es válida, limpiar el estado de error y devolver una tupla con ambos valores igual a -1
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return make_tuple(-1, -1);
    }

    // Devolver una tupla con los valores capturados
    return make_tuple(x, y);
}

int menu()
{
    int opcion = 0;

    // Mostrar opciones del menú
    cout << "1. Mostrar Tablero" << endl;
    cout << "2. Agregar Nave" << endl;
    cout << "4. Listo" << endl;
    cout << "Ingrese su opción: ";
    try
    {

        // Leer la opción del usuario
        if (cin.fail())
        {
            // Limpiar el estado de error del flujo de entrada
            cin.clear();
            // Descartar la entrada incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("No es una entrada válida. \n");
        }
        cin >> opcion;
        // Limpiar el buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }

    return opcion;
}

int main()
{

    unsigned short num_barcos = 3, i = 0, opc = 0;
    Tablero tablero_jugador;
     

    while (i < num_barcos){
        auto coordenadas = capturar_coordenadas();
        cout << "Coordenada X: " << get<0>(coordenadas) << endl;
        cout << "Coordenada X: " << get<1>(coordenadas) << endl;
    }

    do
    {
        opc = menu();

        switch (opc)
        {
        case 0:
            break;
        case 1:
            cout << "Opción 1: Mostrar Tablero" << endl;
            tablero_jugador.muestra_tablero();
            break;
        case 4:
            cout << "Opción 4: Listo" << endl;
            break;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }

    } while (opc != 4);

    return 0;
}
