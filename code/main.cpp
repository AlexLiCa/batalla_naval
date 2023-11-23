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
    cout << "1. Mostrar Tablero" << endl;
    cout << "2. Agregar Barco" << endl;
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
    short barco_elegido = -1, direccion = -1;
    bool disponible;
    tuple<short, short> coordenadas;
    Tablero tablero_jugador;
    vector<Barco> barcos;
    barcos.push_back(Barco('A', 1));
    barcos.push_back(Barco('B', 2));
    barcos.push_back(Barco('C', 3));
    barcos.push_back(Barco('D', 4));

    // while (i < num_barcos){
    //     auto coordenadas = capturar_coordenadas();
    //     cout << "Coordenada X: " << get<0>(coordenadas) << endl;
    //     cout << "Coordenada X: " << get<1>(coordenadas) << endl;
    // }

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
        case 2:
            cout << "Opción 2: Agregar Barco" << endl;
            /*Mostramos barcos disponibles para agregar
            En un futuro verificar tamaño de "barcos" para ver si se puede
                agregar alguno*/
            cout << "Que barco quieres agregar" << endl;
            for (size_t i = 0; i < barcos.size(); i++)
            {
                cout << i << ":";
                barcos[i].muestra_barco();
            }
            /*Pedimos el indice del barco que se quiere agregar*/
            barco_elegido = captura_entero("Barco a agregar: ");
            
            if (barco_elegido >= 0 && barco_elegido < barcos.size())
            {
                cout<< barcos[barco_elegido].get_nombre()<< endl;
                direccion = captura_entero("Direccion: del barco: ");
                cout << direccion << endl;
                /*Pedimos las coordenadas a las que vamos a agregar el barco*/
                coordenadas = capturar_coordenadas();
                cout << get<0>(coordenadas) << get<1>(coordenadas) << endl;
                    /*Verificamos si las coordenadas capturadas son validas*/
                    if (get<0>(coordenadas) > -1 && (direccion == 0 || direccion == 1))
                {
                    disponible = tablero_jugador.checa_posicion(get<0>(coordenadas), get<1>(coordenadas),
                                                                barcos[barco_elegido].get_longitud(), (direccion == 0) ? true : false);
                    if (disponible)
                    {
                        tablero_jugador.coloca_barco(barcos[barco_elegido], get<0>(coordenadas),
                                                     get<1>(coordenadas), (direccion == 0) ? true : false);
                        // tablero_jugador.muestra_tablero();
                    }
                }
            }

        case 4:
            cout << "Opción 4: Listo" << endl;
            break;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }

    } while (opc != 4);

    return 0;
}
