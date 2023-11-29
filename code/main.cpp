#include <iostream>
#include <limits>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib/headers/jugador.h"
#include "lib/headers/juegos.h"

using namespace std;

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
    cout << "4. Hacer un Tiro" << endl;
    cout << "5. Salir" << endl;
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

// int main()
// {
//     Jugador jugador;
//     bool primer_tiro = true;

//     if(!jugador.get_tiene_acceso()){
//         jugador.iniciar_hilo();
//         primer_tiro = false;
//     }

//     int opc = 0;

//     do
//     {
//         opc = menu();
//         switch (opc)
//         {
//         case 1:
//             jugador.muestra_tablero(true);
//             break;
//         case 2:
//             jugador.muestra_tablero(false);
//             break;
//         case 3:
//             cout << endl;
//             jugador.colocar_barco();
//             break;
//         case 4:
//             // if(jugador.get_tablero_listo()){
//                 if(jugador.get_tiene_acceso()){
//                     if(!primer_tiro){
//                         jugador.finalizar_hilo(false);
//                     }
                    
//                     jugador.tirar();
//                     cout << "Termine de Tirar" << endl;
//                 }
//                 else {
//                     cout << "\nEsperando turno";
//                 }
//             // }
//             // else {
//             //     cout << "\nTermina de llenar tu tablero";
//             // }

//             primer_tiro = false;

//             break;
//         case 5:
//             break;
//         default:
//             cout << "Opcion invalida." << endl;
//             break;
//         }

//     } while (opc != 5);

//     return 0;
// }

// main.cpp


int main()
{
    Juegos manager;
    int choice;
    string name;
    bool en_juego = false;

    do
    {
        cout << "Menu:" << endl;
        cout << "1. Crear semaforo" << endl;
        cout << "2. Entrar al semaforo" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Ingrese el nombre del semaforo a crear: ";
            cin >> name;
            manager.createSemaphore(name);
            break;
        case 2:
            cout << "Ingrese el nombre del semaforo al que desea entrar: ";
            cin >> name;
            manager.enterSemaphore(name);
            break;
        case 3:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }

    } while (choice != 3);

    return 0;
}
