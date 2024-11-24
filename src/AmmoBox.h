#pragma once

#include "Item.h"
#include "Pickup.h"

/**
 * @class AmmoBox
 * @brief Representa una caja de munición que puede ser recogida por un jugador.
 *
 * La clase AmmoBox hereda de las clases Item y Pickup. Su propósito es
 * proporcionar munición al jugador cuando es recogida.
 */
class AmmoBox : public Item, public Pickup {
public:
    /**
     * @brief Cantidad de munición contenida en la caja.
     *
     * Inicialmente, cada caja contiene 15 unidades de munición.
     */
    int ammoCount;

    /**
     * @brief Acción para recoger la caja de munición.
     *
     * Este método sobrescribe el comportamiento de Pickup. Si la caja
     * de munición es recogida por el jugador, la cantidad de munición
     * se transfiere al arma actual del jugador.
     *
     * @return true si la munición fue recogida exitosamente, false en caso contrario.
     */
    bool pickup() override;

    /**
     * @brief Constructor de la clase AmmoBox.
     *
     * Inicializa una caja de munición en la posición especificada y asigna
     * la cantidad de munición por defecto (15 unidades).
     *
     * @param pos Posición inicial de la caja en el espacio 2D.
     */
    AmmoBox(Point2D pos);
};
