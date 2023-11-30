// necessary includes -------->
#include "../headers/jugador.h"

#define SEM_NAME "/semaforo_batalla_naval"
#define SHM_NAME "/shm_batalla_naval"

// functions definition -------->
/**
 * @brief Construct a new Jugador:: Jugador object
 *
 * @param fifo_fd
 */
Jugador::Jugador() : tablero_jugador(), tablero_oponente()
{
    this->tablero_listo = false;

    char nombres_barcos[] = {'A', 'B', 'C', 'D'};

    for (int i = 0; i < 4; i++)
    {
        barcos.push_back(Barco(nombres_barcos[i], i + 1));
    }

    this->sem = sem_open(SEM_NAME, 0);

    if (this->sem == SEM_FAILED)
    {
        this->sem = sem_open(SEM_NAME, O_CREAT, 0660, 1);
    }

    this->tiene_acceso = (sem_trywait(this->sem) == 0);

    this->nombre = this->tiene_acceso ? "Jugador 1" : "Jugador 2";

    if (this->tiene_acceso)
    {
        this->shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0660);
    }
    else
    {
        this->shm_fd = shm_open(SHM_NAME, O_RDWR, 0660);
    }

    if (this->shm_fd == -1)
    {
        perror("Error al crear/abrir la memoria compartida");
    }

    if (ftruncate(this->shm_fd, sizeof(mensaje)) == -1)
    {
        perror("Error al configurar el tamaño de la memoria compartida");
    }

    this->memory_ptr = mmap(NULL, sizeof(mensaje), PROT_READ | PROT_WRITE, MAP_SHARED, this->shm_fd, 0);

    if (this->memory_ptr == MAP_FAILED)
    {
        std::cout << "Error while mapping shared memory!" << std::endl;
    }
}

/**
 * @brief Destroy the Jugador:: Jugador object
 * 
 */
Jugador::~Jugador()
{
    close(this->shm_fd);
    shm_unlink(SHM_NAME);

    sem_close(this->sem);
    sem_unlink(SEM_NAME);
}

/**
 * @brief Muestra un tablero del jugador
 *
 * @param del_jugador Define si se muestra el tablero del jugador o el del oponente
 */
void Jugador::muestra_tablero(bool del_jugador)
{
    std::cout << this->tiene_acceso << std::endl;
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
        std::cout << "Seleccione un barco: ";
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
                    if (!this->tablero_jugador.checa_posicion(this->barcos[barco_index], coordenadas.first, coordenadas.second))
                    {
                        std::cout << "Alguna de las coordenadas ya esta ocupada" << std::endl;
                    }
                } while (!this->tablero_jugador.checa_posicion(this->barcos[barco_index], coordenadas.first, coordenadas.second));

                this->tablero_jugador.coloca_barco(this->barcos[barco_index], coordenadas.first, coordenadas.second);

                std::cout << "Barco Colocado Correctamente" << std::endl;

                break;

            default:
                break;
            }

        } while (op_barco != 2);

        if (barcos_colocados == this->barcos.size() - 1)
        {
            this->tablero_listo = true;
        }
    }
}

/**
 * @brief Alterna la variable de acceso al semaforo
 * 
 */
void Jugador::cambia_acceso()
{
    this->tiene_acceso = !this->tiene_acceso;
};

/**
 * @brief Recupera la variable de acceso al semaforo
 * 
 * @return true cuando tiene acceso | 
 * @return false cuando no se tiene acceso
 */
bool Jugador::get_tiene_acceso()
{
    return this->tiene_acceso;
};

/**
 * @brief Limpia el archivo de historial
 * 
 * @param nombreArchivo 
 */
void Jugador::limpiar_archivo(const char *nombreArchivo)
{
    // Truncar el archivo para vaciarlo
    int fileDescriptor = open(nombreArchivo, O_WRONLY | O_TRUNC | O_CREAT, 0666);

    if (fileDescriptor == -1)
    {
        std::cerr << "Error al limpiar el archivo." << std::endl;
        return;
    }

    close(fileDescriptor);
}

/**
 * @brief Escribe la información en el historial
 * 
 * @param tiro_info Estructura que lleva la información del tiro
 */
void Jugador::escribirEnArchivo(mensaje tiro_info)
{
    int fileDescriptor = open("Historial.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (fileDescriptor == -1)
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    std::string x = std::to_string(tiro_info.coordenadas[0]);
    std::string y = std::to_string(tiro_info.coordenadas[1]);
    char valor[] = {tiro_info.valor};

    // Escribir en el archivo en el formato "Nombre: texto"
    write(fileDescriptor, this->nombre.c_str(), this->nombre.size());
    write(fileDescriptor, "\n", 1);
    write(fileDescriptor, "x: ", 3);
    write(fileDescriptor, x.c_str(), x.size());
    write(fileDescriptor, "\n", 1);
    write(fileDescriptor, "y: ", 3);
    write(fileDescriptor, y.c_str(), y.size());
    write(fileDescriptor, "\n", 1);
    write(fileDescriptor, "valor: ", 6);
    write(fileDescriptor, valor, 1);
    write(fileDescriptor, "\n", 1);

    close(fileDescriptor);
}

/**
 * @brief Funcion ejecutada por el hilo para esperar a que el otro jugador tire
 * 
 * @param acaba verifica si el juego debe acabar o no
 */
void Jugador::esperando_turno(short &acaba)
{
    try{
        sem_wait(this->sem);

        mensaje *recibido = static_cast<mensaje *>(this->memory_ptr);

        std::cout << "\n\nRecibiendo impacto" << std::endl;
        std::cout << "x= " << recibido->coordenadas[0] << ", y= " << recibido->coordenadas[1] << std::endl;

        char resultado = this->tablero_jugador.tira(recibido->coordenadas[0], recibido->coordenadas[1]);

        if (resultado == 'O')
        {
            for (unsigned short i = 0; i< this->barcos.size(); i++)
            {
                if (this->barcos[i].checa_coordenadas(recibido->coordenadas[1], recibido->coordenadas[0]))
                {
                    this->barcos[i].actualizar_vida();

                    break;
                }
            }
        }
        else if (resultado == 'T')
        {
            resultado = 'O';
        }
        
        if(this->aun_hay_barcos()){
            recibido->valor = resultado;
        }
        else {
            recibido->valor = 'G';
            acaba = -1;
        }

        std::cout << (resultado == 'O' ? "Nos dio" : "Fallo") << std::endl;

        sem_post(this->sem);

        sleep(2);

        sem_wait(this->sem);

        this->cambia_acceso();
    }
    catch(...){

    }
}

/**
 * @brief Operación de tirar de un proceso a otro
 * 
 * @param acaba lleva el control si el juego debe acabar
 */
void Jugador::tirar(short &acaba)
{
    mensaje *enviado = static_cast<mensaje *>(this->memory_ptr);

    std::pair<unsigned short, unsigned short> coordenadas = capturar_coordenadas();

    enviado->coordenadas[0] = coordenadas.first;
    enviado->coordenadas[1] = coordenadas.second;
    enviado->valor = ' ';

    sem_post(this->sem);

    sleep(1);

    sem_wait(this->sem);

    mensaje *recibido = static_cast<mensaje *>(this->memory_ptr);

    if(recibido->valor == 'G'){
        this->tablero_oponente.tira(recibido->coordenadas[0], recibido->coordenadas[1], 'O');
        acaba = 1;
    }
    else {
        this->tablero_oponente.tira(recibido->coordenadas[0], recibido->coordenadas[1], recibido->valor);
    }

    char valor = recibido->valor == 'G'? 'O' : recibido->valor;

    std::cout << (valor == 'O' ? "Le diste" : "Fallaste") << std::endl;

    this->escribirEnArchivo(*recibido);

    sem_post(this->sem);

    this->cambia_acceso();

    sleep(2);

    this->iniciar_hilo(acaba);
}

/**
 * @brief Finaliza el hilo creado para interactuar con el otro procesp
 * 
 * @param exit 
 */
void Jugador::finalizar_hilo(bool exit = false)
{
    if (this->hilo.joinable())
    {
        this->hilo.join();
    }
}

/**
 * @brief Inicia el Hilo que va a estar pendiente de la respuesta del contrincante
 * 
 * @param acaba Lleva el control si el juego debe de terminar
 */
void Jugador::iniciar_hilo(short &acaba)
{
    this->hilo = std::thread(&Jugador::esperando_turno, this, std::ref(acaba));
}

/**
 * @brief Regresa si el jugador ha posicionado todos sus barcos en el tablero
 * 
 * @return true cuando no quedan barcos que posicionar
 * @return false cuando faltan barcos
 */
bool Jugador::get_tablero_listo()
{
    return this->tablero_listo;
}

/**
 * @brief Otorga un resumen de la vida de cada barco
 * 
 */
void Jugador::resumen_barcos()
{
    for (Barco barco : this->barcos)
    {
        if(barco.get_vida() > 0)
        {
            std::cout << barco.get_nombre() << " -- " << "Vidas Restante: " << barco.get_vida() << std::endl;   
        }
        else 
        {
            std::cout << barco.get_nombre() << " -- " << "Hundido" << std::endl;
        }
    }
}

/**
 * @brief Imprime las posiciones de los barcos en el tablero
 * 
 */
void Jugador::posiciones_barcos()
{
    for (Barco barco : this->barcos)
    {
        std::cout << barco.get_nombre() << " -- Posiciones" << std::endl;
        for (std::pair<unsigned short, unsigned short> pair : barco.get_posiciones())
        {
            std::cout << "x: " << pair.second << " | y: " << pair.first << std::endl;
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Verifica si el jugador aun tiene barcos con vida
 * 
 * @return true cuando el jugador aun tiene barcos | 
 * @return false cuando todos los barcos se han hundido
 */
bool Jugador::aun_hay_barcos(){
    for(Barco barco : this->barcos){
        if(barco.get_vida() > 0){
            return true;
        }
    }
    
    return false;
}