#include <iostream>
#include <limits>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lib/headers/jugador.h"

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

int menu_juegos()
{
    int opcion = 0;

    // Mostrar opciones del menú
    cout << "\n"
         << endl;
    cout << "Menu:" << endl;
    cout << "1. Crear semáforo" << endl;
    cout << "2. Acceder al semáforo" << endl;
    cout << "3. Salir" << endl;
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

bool crearSemaforo(const char *nombre)
{
    // Intentar crear el semáforo
    sem_t *sem = sem_open(nombre, O_CREAT | O_EXCL, 0644, 2);

    if (sem == SEM_FAILED)
    {
        // El semáforo ya existe
        cerr << "Error: No se pudo crear el semáforo. Ya existe." << endl;
        return false;
    }
    else
    {
        // El semáforo se creó exitosamente
        cout << "Semaforo creado exitosamente." << endl;
        return true;
    }
}

bool accederSemaforo(const char *nombre)
{
    // Intentar acceder al semáforo
    sem_t *sem = sem_open(nombre, O_RDWR);

    if (sem == SEM_FAILED)
    {
        // El semáforo no existe
        cerr << "No se pudo acceder al semáforo. " << endl;
        return false;
    }
    else
    {
        // El semáforo se accedió exitosamente
        cout << "Semaforo accedido exitosamente." << endl;

        // Hacer algo con el semáforo, si es necesario
        return true;
    }
}

int main()
{
    bool semaforoAccedido = false;
    string nombreSemaforo;
    int opcion_juegos = 0;

    while (!semaforoAccedido)
    {
        opcion_juegos = menu_juegos();

        switch (opcion_juegos)
        {
        case 1:
            cout << "Ingrese el nombre del juego a crear: ";
            cin >> nombreSemaforo;
            nombreSemaforo = "/" + nombreSemaforo;
            semaforoAccedido = crearSemaforo(nombreSemaforo.c_str());
            break;
        case 2:
            cout << "Ingrese el nombre del juego al que desea acceder: ";
            cin >> nombreSemaforo;
            nombreSemaforo = "/" + nombreSemaforo;
            semaforoAccedido = accederSemaforo(nombreSemaforo.c_str());
            break;
        case 3:
            cout << "Saliendo..." << endl;
            exit(0);
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }

    if (semaforoAccedido)
    {
        Jugador jugador(nombreSemaforo);
        bool primer_tiro = true;

        if (!jugador.get_tiene_acceso())
        {
            jugador.iniciar_hilo();
            primer_tiro = false;
        }

        int opc = 0;

        do
        {
            opc = menu();
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
                // if(jugador.get_tablero_listo()){
                if (jugador.get_tiene_acceso())
                {
                    if (!primer_tiro)
                    {
                        jugador.finalizar_hilo(false);
                    }

                    jugador.tirar();
                    cout << "Termine de Tirar" << endl;
                }
                else
                {
                    cout << "\nEsperando turno";
                }
                // }
                // else {
                //     cout << "\nTermina de llenar tu tablero";
                // }

                primer_tiro = false;

                break;
            case 5:
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
            }

        } while (opc != 5);
    }

    //sem_unlink(nombreSemaforo.c_str());

    return 0;
}
