#pragma once

/**
 * @class Pickup
 * @brief Clase base abstracta para objetos recogibles en el juego.
 *
 * Esta clase define una interfaz para todos los objetos que pueden ser recogidos
 * por el jugador u otros elementos en el juego.
 */
class Pickup {
public:
    /**
     * @brief Método virtual puro para definir la acción de recoger el objeto.
     *
     * Este método debe ser implementado por las clases derivadas, especificando
     * el comportamiento cuando el objeto es recogido.
     *
     * @return Un valor booleano que indica si el objeto fue recogido con éxito.
     */
    virtual bool pickup() = 0;
};