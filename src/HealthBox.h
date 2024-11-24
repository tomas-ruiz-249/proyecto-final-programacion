#pragma once
#include "Item.h"
#include "Pickup.h"

/**
 * @class HealthBox
 * @brief Representa un objeto que otorga puntos de curación al jugador.
 *
 * La clase `HealthBox` es un tipo especial de ítem que, al ser recogido,
 * incrementa la salud del jugador. Hereda de las clases `Item` y `Pickup`.
 */
class HealthBox : public Item, public Pickup {
public:
    int healingPoints; ///< Puntos de curación que otorga el HealthBox.

    /**
     * @brief Constructor de la clase HealthBox.
     *
     * @param pos Posición del HealthBox en el espacio (tipo Point2D).
     *
     * Crea un nuevo objeto `HealthBox` con una posición inicial y establece
     * por defecto los puntos de curación a 30.
     */
    HealthBox(Point2D pos);

    /**
     * @brief Método que recoge el HealthBox y cura al jugador.
     *
     * @return true si el objeto se usó correctamente, false en caso contrario.
     *
     * Este método interactúa con la clase `Player` para incrementar la salud
     * del jugador en función de los puntos de curación (`healingPoints`).
     */
    bool pickup() override;
};
