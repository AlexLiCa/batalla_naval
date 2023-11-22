#include <iostream>
#include <vector>
using namespace std;

// Función para crear una matriz con todos los valores inicializados en "0"
vector<vector<char>> crearMatriz(int filas, int columnas)
{
    // Inicializar la matriz con todos los valores en "0"
    vector<vector<char>> matriz(filas, vector<char>(columnas, '0'));
    return matriz;
}

/* Función para imprimir la matriz creada por el usuario */
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

/*
Función para cambiar el un valor de un elemento especifico de la matriz
*/
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

int main()
{
    int filas = 5, columnas = 5;

    // Crear la matriz del jugador
    vector<vector<char>> tablero_jugador = crearMatriz(filas, columnas);

    // Crear la matriz del oponente
    vector<vector<char>> tablero_oponente = crearMatriz(filas, columnas);

    // Imprimir la matriz creada
    cout << "Matriz creada:\n";
    imprimirMatriz(tablero_jugador);

    // Cambiar un valor en la matriz
    int filaCambio, columnaCambio;
    cout << "Ingrese la fila y la columna donde desea cambiar el valor (ejemplo: 2 3): ";
    cin >> filaCambio >> columnaCambio;
    char barco = 'N';
    int cambio = cambiarValorMatriz(tablero_jugador, filaCambio, columnaCambio, barco);
    cout << (cambio == 1 ? "Se agrego el barco " : "Fuera del limite del tablero") << endl;
    imprimirMatriz(tablero_jugador);

    return 0;
}
