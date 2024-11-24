#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

/**
 * @class Item
 * @brief Clase base para los elementos del juego interactuables.
 *
 * La clase `Item` define los elementos básicos de un objeto en el juego,
 * como su posición y sprite asociado. Está pensada para ser una clase base
 * que puede ser heredada por otros objetos más específicos, como HealthBox.
 */
class Item {
public:
    Point2D position; ///< Posición del objeto en el espacio 2D.
    Drawable* sprite; ///< Sprite asociado para representar el objeto gráficamente.

    /**
     * @brief Constructor por defecto de la clase Item.
     *
     * Inicializa un objeto `Item` con posición predeterminada y sin sprite asociado.
     */
    Item();

    /**
     * @brief Constructor parametrizado de la clase Item.
     *
     * @param position Posición inicial del objeto (tipo Point2D).
     *
     * Inicializa un objeto `Item` con la posición especificada y sin sprite asociado.
     */
    Item(Point2D position);

    /**
     * @brief Destructor virtual por defecto.
     *
     * Permite la correcta destrucción de los objetos derivados de esta clase.
     */
    virtual ~Item() = default;

private:
};
