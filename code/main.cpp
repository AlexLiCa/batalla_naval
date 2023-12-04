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

void waitEnter()
{
    std::string nada;
    std::cout << "Presiona Enter para terminar" << std::endl;
    getline(std::cin, nada);
}

int menu()
{
    int opcion = 0;

    cout << "\n"
         << endl;
    cout << "1. Mostrar Tablero" << endl;
    cout << "2. Mostrar Tablero Oponente" << endl;
    cout << "3. Agregar Barco" << endl;
    cout << "4. Resumen de Barcos" << endl;
    cout << "5. Posiciones de los Barcos" << endl;
    cout << "6. Hacer un Tiro" << endl;
    cout << "7. Salir" << endl;
    cout << "Ingrese su opcion: ";

    try
    {
        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("No es una entrada valida. \n");
        }
        
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

    cout << "\n"
         << endl;
    cout << "1. Crear juego" << endl;
    cout << "2. Unirse a un juego" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese su opcion: ";

    try
    {
        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("No es una entrada valida. \n");
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }

    return opcion;
}

bool crearSemaforo(const char *nombre, sem_t *sem)
{
    sem = sem_open(nombre, O_CREAT | O_EXCL, 0644, 2);

    if (sem == SEM_FAILED)
    {
        cerr << "Por el momento no se puede usar ese nombre" << endl;
        return false;
    }
    else
    {
        cout << "Juego Iniciado correctamente." << endl;
        sem_wait(sem);
        return true;
    }
}

bool accederSemaforo(const char *nombre, sem_t *sem)
{
    sem = sem_open(nombre, 0);

    if (sem == SEM_FAILED)
    {
        cerr << "El juego no existe. " << endl;
        return false;
    }
    else
    {
        if (sem_trywait(sem) == 0)
        {
            cout << "Juego encontrado!" << endl;
            cout << "Estableciendo conexión..." << endl;
            sleep(2);
            cout << "Conexión exitosa..." << endl;
            return true;
        }

        else
        {
            cout << "No te puedes unir a esta partida..." << endl;
        }
        return false;
    }
}

int main()
{
    bool semaforoAccedido = false;
    string nombre_semaforo;

    int opcion_juegos = 0;
    sem_t *sem;

    while (!semaforoAccedido)
    {
        opcion_juegos = menu_juegos();

        switch (opcion_juegos)
        {
        case 1:
            cout << "Ingrese el nombre del juego a crear: ";
            cin >> nombre_semaforo;
            nombre_semaforo = "/" + nombre_semaforo;
            semaforoAccedido = crearSemaforo(nombre_semaforo.c_str(), sem);
            break;
        case 2:
            cout << "Ingrese el nombre del juego al que desea acceder: ";
            cin >> nombre_semaforo;
            nombre_semaforo = "/" + nombre_semaforo;
            semaforoAccedido = accederSemaforo(nombre_semaforo.c_str(), sem);
            break;
        case 3:
            cout << "Saliendo..." << endl;
            exit(0);
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }

    if (semaforoAccedido && opcion_juegos != 3)
    {
        Jugador jugador(nombre_semaforo);
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
                    jugador.rage_quit(acabo);
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
        else if(acabo == -2){
            cout << "Alguien ya no quizo jugar..." << endl;
        }

        waitEnter();
    }


    sem_close(sem);
    sem_unlink(nombre_semaforo.c_str());

    return 0;
}
