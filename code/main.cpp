#include <iostream>
#include <vector>
#include <limits>
#include "lib/headers/tablero.h"
#include "lib/headers/barco.h"
#include "lib/headers/jugador.h"

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

short captura_entero(string caption)
{
    short numero = 0;
    cout << caption;
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
        cin >> numero;
        // Limpiar el buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (const invalid_argument &e)
    {
        numero = -1;
        cerr << e.what() << endl;
    }
    return numero;
}

int menu()
{
    int opcion = 0;

    // Mostrar opciones del menú
    cout << "\n"
         << endl;
    cout << "1. Mostrar Tablero" << endl;
    cout << "2. Mostrar Tablero Oponente" << endl;
    cout << "3. Agregar Barco" << endl;
    cout << "4. Salir" << endl;
    cout << "Ingrese su opcion: ";

    try
    {
        // Leer la opción del usuario
        if (!(cin >> opcion))
        {
            // Limpiar el estado de error del flujo de entrada
            cin.clear();
            // Descartar la entrada incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("No es una entrada valida. \n");
        }
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
    Jugador jugador;
    int opc = 0;

    do
    {
        opc = menu();

        switch (opc)
        {
        case 0:
            break;
        case 1:
            jugador.muestra_tablero(true);
            break;
        case 2:
            jugador.muestra_tablero(false);
            break;
        case 3:
            cout << endl;
            jugador.colocar_barco();
            break;
        case 4:
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opc != 4);

    return 0;
}
