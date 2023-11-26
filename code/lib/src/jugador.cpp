// necessary includes -------->
#include "../headers/jugador.h"

// functions definition -------->
/**
 * @brief Crea una nueva instancia de un Jugador
 *
 */
Jugador::Jugador(void) : tablero_jugador(), tablero_oponente()
{
    this->tablero_listo = false;

    char nombres_barcos[] = {'A', 'B', 'C', 'D'};

    for (int i = 0; i < 4; i++)
    {
        barcos.push_back(Barco(nombres_barcos[i], i + 1));
    }
}

/**
 * @brief Muestra un tablero del jugador
 *
 * @param del_jugador Define si se muestra el tablero del jugador o el del oponente
 */
void Jugador::muestra_tablero(bool del_jugador)
{
    del_jugador ? this->tablero_jugador.muestra_tablero() : this->tablero_oponente.muestra_tablero();
}

/**
 * @brief Otorga un menu de opciones para realizar con un barco
 *
 * @param barco Barco sobre el que se harán las operaciones
 * @return unsigned short opción elegida por el usuario
 */
unsigned short menu_barco(Barco &barco)
{
    unsigned short opcion = 0;

    // Mostrar opciones del menú
    std::cout << "\n";
    barco.muestra_barco();
    std::cout << "1. Cambiar Orientacion" << std::endl;
    std::cout << "2. Colocar en Tablero" << std::endl;
    std::cout << "Ingrese su opcion: ";

    try
    {
        // Leer la opción del usuario
        if (!(std::cin >> opcion))
        {
            // Limpiar el estado de error del flujo de entrada
            std::cin.clear();
            // Descartar la entrada incorrecta
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("No es una entrada valida. \n");
        }
        // Limpiar el buffer de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return opcion;
}

/**
 * @brief Captura coordenadas para colocar un barco
 *
 * @return std::pair<unsigned short, unsigned short>
 */
std::pair<unsigned short, unsigned short> capturar_coordenadas()
{
    unsigned short x, y;

    std::cout << "Ingresa dos valores (x y): ";
    while (!(std::cin >> x >> y))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ingresa dos valores (x y): ";
    }

    return {x, y};
}

/**
 * @brief Coloca un barco del jugador después de seleccionarlo
 *
 */
void Jugador::colocar_barco()
{
    unsigned short barcos_colocados = 0;

    for (short i = 0; i < this->barcos.size(); i++)
    {
        if (this->barcos[i].get_colocado())
        {
            barcos_colocados++;
        }
        else
        {
            std::cout << i << ": ";
            this->barcos[i].muestra_barco();
        }
    }

    if (barcos_colocados == this->barcos.size())
    {
        std::cout << "No Hay Barcos que colocar" << std::endl;
    }
    else
    {
        unsigned short barco_index = -1;
        std::cout << "Seleccione un barco: " << std::endl;
        while (!(std::cin >> barco_index))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "\nBarco Seleccionado: " << this->barcos[barco_index].get_nombre() << std::endl;

        unsigned short op_barco;
        std::pair<unsigned short, unsigned short> coordenadas;
        do
        {
            op_barco = menu_barco(this->barcos[barco_index]);

            switch (op_barco)
            {
            case 1:
                this->barcos[barco_index].cambiar_dir();
                break;

            case 2:
                do
                {
                    coordenadas = capturar_coordenadas();
                } while (!this->tablero_jugador.checa_posicion(this->barcos[barco_index], coordenadas.first, coordenadas.second));

                this->tablero_jugador.coloca_barco(this->barcos[barco_index], coordenadas.first, coordenadas.second);

                std::cout << "Barco Colocado Correctamente" << std::endl;

                break;

            default:
                break;
            }

        } while (op_barco != 2);
    }
}
