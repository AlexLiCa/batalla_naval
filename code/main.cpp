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

/*Funcion para capturar un entero corto
    Recibe:
        -Una cadena que se imprime en consola antes de capturar el dato*
    Regresa:
        El numero capturado
        -1 en caso de que el usuario no ingrese un numero*/
short captura_entero(string caption)
{
    short numero = -1;
    cout << caption;
    try
    {
        cin >> numero;
        // Limpiar el buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Leer la opción del usuario
        if (cin.fail())
        {
            numero = -1;
            // Limpiar el estado de error del flujo de entrada
            cin.clear();
            // Descartar la entrada incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("\nNo es una entrada válida. \n");
        }
    }
    catch (const invalid_argument &e)
    {
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
    cout << "3. Tira" << endl;
    cout << "4. Listo" << endl;
    cout << "Ingrese su opción: ";
    try
    {
        cin >> opcion;
        // Limpiar el buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Leer la opción del usuario
        if (cin.fail())
        {
            // Limpiar el estado de error del flujo de entrada
            cin.clear();
            // Descartar la entrada incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
            throw invalid_argument("\nNo es una entrada válida. \n");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }

    return opcion;
}

int main()
{

    unsigned short num_barcos = 3, i = 0, opc = 0, tiro;
    short barco_elegido, direccion = -1;
    bool disponible;
    tuple<short, short> coordenadas;
    Tablero tablero_jugador;
    vector<Barco> barcos_disponibles, barcos_usados;
    barcos_disponibles.push_back(Barco('A', 1));
    barcos_disponibles.push_back(Barco('B', 2));
    barcos_disponibles.push_back(Barco('C', 3));
    barcos_disponibles.push_back(Barco('D', 4));

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
            /*Mostramos barcos_disponibles disponibles para agregar
            En un futuro verificar tamaño de "barcos_disponibles" para ver si se puede
                agregar alguno*/
            for (size_t i = 0; i < barcos_disponibles.size(); i++)
            {
                cout << i << ":";
                barcos_disponibles[i].muestra_barco();
            }
            /*Pedimos el indice del barco que se quiere agregar*/
            barco_elegido = captura_entero("Barco a agregar: ");

            /* Verificamso que exista el barco y que sea un indice valido */
            if (barco_elegido >= 0 && barco_elegido < barcos_disponibles.size())
            {
                // cout << barcos_disponibles[barco_elegido].get_nombre() << endl;
                direccion = captura_entero("Direccion del barco(0:Horizontal, 1:Vertical): ");
                cout << direccion << endl;
                /*Pedimos las coordenadas a las que vamos a agregar el barco*/
                coordenadas = capturar_coordenadas();
                cout << "(" << get<0>(coordenadas) << "," << get<1>(coordenadas) << ")" << endl;
                /*Verificamos si las coordenadas capturadas son validas*/
                if (get<0>(coordenadas) > -1 && (direccion == 0 || direccion == 1))
                {
                    disponible = tablero_jugador.checa_posicion(get<0>(coordenadas), get<1>(coordenadas),
                                                                barcos_disponibles[barco_elegido].get_longitud(), (direccion == 0) ? true : false);
                    if (disponible)
                    {
                        tablero_jugador.coloca_barco(barcos_disponibles[barco_elegido], get<0>(coordenadas),
                                                     get<1>(coordenadas), (direccion == 0) ? true : false);
                        // tablero_jugador.muestra_tablero();
                    }
                    else
                    {
                        cout << "\nNo se puede agregar el barco en esa posicion\n"
                             << endl;
                    }
                }
                else
                {
                    cout << "\nCoordenadas o direccion Invalidas\n"
                         << endl;
                }
            }
            else
            {
                cout << "\nEl barco no existe \n"
                     << endl;
            }
            break;
        case 3:
            cout << "Opción 3: Tirar" << endl;
            coordenadas = capturar_coordenadas();
            if ((get<0>(coordenadas) > -1 && get<0>(coordenadas) < 10) && (get<1>(coordenadas) > -1 && get<1>(coordenadas) < 10))
            {
                tiro = tablero_jugador.tira(get<0>(coordenadas), get<1>(coordenadas));
                if (tiro == 0)
                {
                    cout << "Fallaste" << endl;
                }
                else if (tiro == 1)
                {
                    cout << "Le diste a un barco !" << endl;
                }
                else if (tiro == 2)
                {
                    cout << "Ya no quedan mas barcos" << endl;
                }
                else if (tiro == 3)
                {
                    cout << "Ya habias tirado ahi" << endl;
                }
                else {
                    cout << "Parece que hubo un error" << endl; 
                }
            }

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
