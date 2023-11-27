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

int main()
{
    sem_t *semaforo = sem_open("/semaforo_batalla_naval", O_CREAT, 0660, 1);

    if (semaforo == SEM_FAILED) {
        cout << "Error al crear el semáforo" << endl;
        semaforo = sem_open("/semaforo_batalla_naval", 0);
    }

    int r = mkfifo("./FIFO", 00660);
    do
    {
        remove("./FIFO");
        r = mkfifo("./FIFO", 00660);
    } while (r == -1);
    int fifo_fd = open("./FIFO", O_RDWR);

    Jugador jugador(*semaforo, fifo_fd);


    if(jugador.get_tiene_acceso()){

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
            // Tener un hilo con promesa y futuro
            // Se debe crear un hilo con una función que intente entrar a una sección critica mediante un semaforo
            // Una vez que se tenga acceso a la sección debe leer el contenido de la tubería
            // Debe contestar si el resultado de la promesa fue un golpe o no
            // Debe registrarse de vuelta la respuesta y regresar la sección critica al que contesto 
            

            // La poseción de la sección critica se mantiene hasta haber hecho un tiro y recibido la respuesta 


            break;
        case 5:
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opc != 5);


    
    sem_close(semaforo); /* Cerramos el semáforo porque no lo vamos a utilizar más */
    sem_unlink("/semaforo_batalla_naval");
    close(fifo_fd);
    unlink("./FIFO");

    return 0;
}
