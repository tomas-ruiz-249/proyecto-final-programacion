#pragma once
#include "Item.h"

/**
 * @class Lamp
 * @brief Representa una lámpara en el juego.
 *
 * La clase `Lamp` es un objeto derivado de `Item` que representa una lámpara
 * con una posición específica y un color asociado. Es útil para agregar elementos
 * visuales o interactivos al juego.
 */
class Lamp : public Item {
public:
    int LampColor; ///< Color de la lámpara representado como un entero.

    /**
     * @brief Constructor de la clase Lamp.
     *
     * @param pos Posición inicial de la l�mpara en el espacio (tipo Point2D).
     *
     * Inicializa una lómpara con una posición especificada. El color de la lámpara
     * debe ser configurado posteriormente.
     */
    Lamp(Point2D pos);
};
