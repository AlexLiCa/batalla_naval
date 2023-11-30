#include <iostream>
#include <limits>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include "lib/headers/jugador.h"

using namespace std;

void waitEnter(){
    std::string nada;
    std::cout << "Presiona Enter para terminar" << std::endl;
    getline(std::cin, nada);
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
    cout << "4. Resumen de Barcos" << endl;
    cout << "5. Posiciones de los Barcos" << endl;
    cout << "6. Hacer un Tiro" << endl;
    cout << "7. Cancelar Juego" << endl;
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
    bool primer_tiro = true;
    short acabo = 0;

    if (!jugador.get_tiene_acceso())
    {
        jugador.iniciar_hilo(acabo);
        primer_tiro = false;
    }

    int opc = 0;

    do
    {
        opc = menu();

        if(acabo == 0){
            switch (opc)
            {
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
                cout << endl;
                jugador.resumen_barcos();
                break;
            case 5:
                cout << endl;
                jugador.posiciones_barcos();
                break;
            case 6:
                if(jugador.get_tablero_listo()){
                    if (jugador.get_tiene_acceso())
                    {
                        if (!primer_tiro)
                        {
                            jugador.finalizar_hilo(false);
                        }

                        jugador.tirar(acabo);
                    }
                    else
                    {
                        std::cout << "\nEsperando turno";
                    }
                }
                else {
                    std::cout << "\nTermina de llenar tu tablero";
                }

                primer_tiro = false;

                break;
            case 7:
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
            }
        }
    } while (opc != 7 && acabo == 0);

    if(acabo == 1){
        cout << "Ganaste!!" << endl;
    }
    else if(acabo == -1){
        cout << "Perdiste..." << endl;
    }

    waitEnter();

    return 0;
}
