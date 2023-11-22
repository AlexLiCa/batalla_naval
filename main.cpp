#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Función para crear una matriz con todos los valores inicializados en "0"
vector<vector<char>> crearMatriz(int filas, int columnas)
{
    // Inicializar la matriz con todos los valores en "0"
    vector<vector<char>> matriz(filas, vector<char>(columnas, '0'));
    return matriz;
}

/* Función para imprimir la matriz creada por el usaurio */
void imprimirMatriz(const vector<vector<char>> &matriz)
{
    for (const auto &fila : matriz)
    {
        for (char valor : fila)
        {
            cout << valor << " ";
        }
        cout << endl;
    }
}

/*Funcion para cambiar el un valor de un elemento especifico de la matriz */
int cambiarValorMatriz(vector<vector<char>> &matriz, int fila, int columna, char valor)
{
    // Obtener la cantidad de filas y columnas
    int filas = matriz.size();
    int columnas = (filas > 0) ? matriz.at(0).size() : 0;
    // Verificar que la fila y la columna estén dentro de los límites de la matriz
    if (fila >= 0 && fila < filas && columna >= 0 && columna < columnas)
    {
        // Cambiar el valor de '0' a valor
        matriz[fila][columna] = valor;

        return 1;
    }
    else
    {
        return -1;
    }
}

// Función para encontrar coordenadas que contienen un valor dado, las regresa en un vector con las coordenadas encontradas
vector<pair<int, int>> encontrarCoordenadas(const vector<vector<char>> &matriz, char valor)
{
    vector<pair<int, int>> coordenadas;

    for (int i = 0; i < matriz.size(); ++i)
    {
        for (int j = 0; j < matriz[i].size(); ++j)
        {
            if (matriz[i][j] == valor)
            {
                coordenadas.push_back({i, j});
            }
        }
    }

    return coordenadas;
}

/*Funcion para agregar una 'n' a las [fila][columna] en caso de que el numero
    de 'n' en la matriz sea menor a num_naves

Regresa:
    1 en caso de que se haya agregado la nave en las coordenadas especificas
    2 en caso de que no se agrege por que ya se tiene el numero maximo de naves
    -1 en caso de que haya un error con los indices indicados*/
int agregar_nave(vector<vector<char>> &matriz, int fila, int columna, int num_naves)
{
    vector<pair<int, int>> naves = encontrarCoordenadas(matriz, 'n');
    if (naves.size() < num_naves)
    {
        int cambio = cambiarValorMatriz(matriz, fila, columna, 'n');
        return (cambio == 1) ? 1 : -1;
    }
    else
    {
        return 2;
    }
};

int eliminar_nave(vector<vector<char>> &matriz, vector<pair<int, int>> naves, int indice)
{
    if (indice >= 0 and indice < naves.size())
    {
        matriz[naves[indice].first][naves[indice].second] = '0';
        return 1;
    }
    else
    {
        return -1;
    }
}

/*Funcion para extraer las coordenadas dadas por el usuario
Regresa una tubpla con los dos valores dados
En caso de que uno de los valores no sea valido, regresa el error*/
tuple<int, int> obtenerCoordenadas()
{
    int filaCambio, columnaCambio;

    cout << "Ingrese la fila y la columna donde desea agregar la nave (ejemplo: 2 3): ";
    cin >> filaCambio >> columnaCambio;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Error: Ingrese números válidos para fila y columna.");
    }

    return make_tuple(filaCambio, columnaCambio);
}

/*Funcion que le pide al usuario que ingrese una variable de tipo "int"
    en caso de que no sea un integer regresara un error
Recibe el texto que quieres que se muestre al usuario*/
int captura_int(string caption)
{
    try
    {
        int numero;

        cout << caption;
        cin >> numero;

        if (cin.fail())
        {
            // Limpiar el estado de error del flujo de entrada
            cin.clear();
            // Descartar la entrada incorrecta
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Error: No es un número entero válido.");
        }

        // Aquí puedes trabajar con el número ingresado
        return numero;
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << endl;
    }
}

int mostrarMenu()
{
    int opcion = 0;

    // Mostrar opciones del menú
    cout << "1. Mostrar Tablero" << endl;
    cout << "2. Agregar Nave" << endl;
    cout << "3. Eliminar Nave" << endl;
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
            throw invalid_argument("Error: No es un número entero válido.");
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
    int filas = 5, columnas = 5, num_naves = 3, indice, eliminada = 0;

    // Crear la matriz del jugador
    vector<vector<char>> tablero_jugador = crearMatriz(filas, columnas);

    // Crear la matriz del oponente
    vector<vector<char>> tablero_oponente = crearMatriz(filas, columnas);
    int opc;

    vector<pair<int, int>> naves;

    do
    {
        opc = mostrarMenu();

        switch (opc)
        {
        case 1:
            cout << "Opción 1: Mostrar Tablero" << endl;
            imprimirMatriz(tablero_jugador);
            break;
        case 2:
            cout << "Opción 2: Agregar Nave" << endl;
            try
            {
                auto coordenadas = obtenerCoordenadas();
                int filaCambio = get<0>(coordenadas);
                int columnaCambio = get<1>(coordenadas);

                auto agregada = agregar_nave(tablero_jugador, filaCambio, columnaCambio, num_naves);

                if (agregada == 1)
                {
                    imprimirMatriz(tablero_jugador);
                }
                else
                {
                    cout << "No se pudo agregar" << endl;
                }
            }
            catch (const invalid_argument &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3:
            cout << "Opción 3: Eliminar Nave" << endl;
            naves = encontrarCoordenadas(tablero_jugador, 'n');
            if (naves.size() > 0)
            {
                eliminada = -1;
                // Mostramos los indices de "naves"
                for (size_t i = 0; i < naves.size(); ++i)
                {
                    cout << i << ": (" << naves[i].first << ", " << naves[i].second << ")\n";
                }

                indice = captura_int("Indice a eliminar: ");

                eliminada = -1;

                eliminada = eliminar_nave(tablero_jugador, naves, indice);

                if (eliminada == 1)
                {
                    cout << "Se elimino la nave" << endl;
                    imprimirMatriz(tablero_jugador);
                }
                else
                {
                    cout << "No se pudo eliminar" << endl;
                }
            }
            else
            {
                cout << "No hay naves a eliminar" << endl;
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
