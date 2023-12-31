// necessary includes -------->
#include "../headers/barco.h"
// #include "barco.h"
// #include "barco.h"

// functions definition -------->
Barco::Barco(char nombre, unsigned short longitud)
{
    this->nombre = nombre;
    this->longitud = longitud;
    this->vida = longitud;

    this->colocado = false;
    this->dir = true;
}

/**
 * @brief Muestra la información del barco en la terminal
 *
 */
void Barco::muestra_barco() const
{
    std::cout << this->nombre << " -- " << this->longitud << " -- " << (this->dir ? "V" : "H") << std::endl;
}

/**
 * @brief Regresa la longitud de un barco
 *
 * @return unsigned short
 */
unsigned short Barco::get_longitud()
{
    return this->longitud;
}
/**
 * @brief Regresa la dirección del barco
 *
 * @return true: Vertical |
 * @return false: Horizontal
 */
bool Barco::get_direccion()
{
    return this->dir;
}

/**
 * @brief Agrega una coordenada al arreglo de posiciones del Barco
 *
 * @param x Coordenada en x
 * @param y Coordenada en y
 */
void Barco::agrega_coordenada(unsigned short x, unsigned short y)
{
    this->posiciones.push_back({y, x});

    if (this->posiciones.size() == this->longitud)
    {
        this->colocado = true;
    }
}

/**
 * @brief Indica si el barco fue colocado en el tablero
 *
 * @return true Cuando el barco ha sido colocado correctamente |
 * @return false Cuando el barco aún no esta colocado
 */
bool Barco::get_colocado()
{
    return this->colocado;
}

/**
 * @brief Recupera el Nombre asignado al Barco
 *
 * @return char
 */
char Barco::get_nombre()
{
    return this->nombre;
}

/**
 * @brief Cambia la direccion actual del barco
 *
 */
void Barco::cambiar_dir()
{
    this->dir = !this->dir;
}

/**
 * @brief Verifica si un barco tiene en sus posiciones las coordenadas dadas
 * 
 * @param x coordenada en x
 * @param y coordenada en y
 * @return true cuando el barco si tiene las coordenadas dadas |
 * @return false cuando el barco no se encuentra en esas coordenadas
 */
bool Barco::checa_coordenadas(unsigned short x, unsigned short y)
{
    for (std::pair<unsigned short, unsigned short> coordenada : this->posiciones)
    {
        if (coordenada.first == y && coordenada.second == x)
        { 
            return true;
        }
    }
    return false;
}

/**
 * @brief Disminuye la vida del barco
 * 
 */
void Barco::actualizar_vida()
{
    this->vida--;
}

/**
 * @brief Regresa la vida del barco del jugador
 * 
 * @return unsigned short vida del barco
 */
unsigned short Barco::get_vida()
{
    return this->vida;
}

/**
 * @brief Retorna el vector de las posiciones del barco en el tablero
 * 
 * @return std::vector<std::pair<unsigned short, unsigned short>> posiciones
 */
std::vector<std::pair<unsigned short, unsigned short>> Barco::get_posiciones()
{
    return this->posiciones;
}