// necessary includes -------->
#include "../headers/tablero.h"

// functions definition -------->
/**
 * @brief Constructor de un Tablero
 *
 */
Tablero::Tablero()
{
    this->tablero = {
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    };
}

/**
 * @brief Coloca un Barco en el tablero
 *
 * @param barco Referencia al barco que se quiere colocar
 * @param x1 Posición Inicial en x
 * @param y1 Posición Inicial en y
 * @return Mensajes de error en caso de que la colocación falle
 */
void Tablero::coloca_barco(Barco &barco, unsigned short x1, unsigned short y1)
{
    unsigned short pos_inicial = barco.get_direccion() ? y1 : x1;

    for (unsigned short i = pos_inicial; i < pos_inicial + barco.get_longitud(); i++)
    {
        if (barco.get_direccion())
        {
            tablero[i][x1] = barco.get_nombre();
            barco.agrega_coordenada(i, x1);
        }
        else
        {
            tablero[y1][i] = barco.get_nombre();
            barco.agrega_coordenada(y1, i);
        }
    }
}

/**
 * @brief Verifica si el barco se puede colocar dependiendo de una posición Inicial
 *
 * @param x Posición Inicial en x
 * @param y Posición Inicial en y
 * @param barco Referencia al barco que se quiere colocar
 * @return true: Cuando el barco se puede colocar en la posicion indicada |
 * @return false: Cuando el barco se sale del tablero o ya hay un barco ocupando la posición
 */
bool Tablero::checa_posicion(Barco &barco, unsigned short x, unsigned short y)
{
    unsigned short pos_inicial = barco.get_direccion() ? y : x;

    unsigned short pos_final = pos_inicial + barco.get_longitud();

    if (pos_final > this->tablero.size())
    {
        return false;
    }

    for (unsigned short i = pos_inicial; i < pos_final; ++i)
    {
        char valor_actual = barco.get_direccion() ? this->tablero[i][x] : this->tablero[y][i];

        if (valor_actual != '0')
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief Imprime el tablero en la terminal
 *
 */
void Tablero::muestra_tablero()
{
    for (short i = 0; i < 50; i++)
    {
        std::cout << "\n";
    }

    std::string separador = "  +---------------------------------------+";

    std::cout << "  ";
    for (short i = 0; i < this->tablero.size(); i++)
    {
        std::cout << std::setw(3) << i << " ";
    }
    std::cout << std::endl;
    std::cout << separador << std::endl;

    for (short int i = 0; i < this->tablero.size(); i++)
    {
        std::cout << i << " | ";
        for (short int j = 0; j < this->tablero[i].size(); j++)
        {
            char valor_a_imprimir = this->tablero[i][j] != '0' ? this->tablero[i][j] : ' ';

            std::cout << valor_a_imprimir << " | ";
        }
        std::cout << std::endl;
        std::cout << separador << std::endl;
    }
}

/**
 * @brief Efectua la acción de tiro en un tablero y actualiza el valor en el tablero
 * 
 * @param x coordenada en x
 * @param y coordenada en y
 * @return char resultado del tiro | X = fallaste | O = acertaste | T = tiro duplicado
 */
char Tablero::tira(unsigned short x, unsigned short y)
{
    if(this->tablero[y][x] == '0' || this->tablero[y][x] == 'X'){
        
        if(this->tablero[y][x] == '0' ){
            this->tablero[y][x] = 'X';
        }
        
        return 'X';
    }
    else if(this->tablero[y][x] == 'O'){
        return 'T';
    }
    else{
        this->tablero[y][x] = 'O';
    }
    
    return 'O';
}

/**
 * @brief Cambia un valor en el tablero
 * 
 * @param x coordenada en x
 * @param y coordenada en y
 * @param valor Nuevo valor que debe tener la coordenada
 */
void Tablero::tira(unsigned short x, unsigned short y, char valor)
{
    this->tablero[y][x] = valor;
}
