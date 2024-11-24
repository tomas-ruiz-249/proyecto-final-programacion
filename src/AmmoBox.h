#pragma once

#include "Item.h"
#include "Pickup.h"

/**
 * @class AmmoBox
 * @brief Representa una caja de munici�n que puede ser recogida por un jugador.
 *
 * La clase AmmoBox hereda de las clases Item y Pickup. Su prop�sito es
 * proporcionar munici�n al jugador cuando es recogida.
 */

class AmmoBox : public Item, public Pickup {
public:
    /**
     * @brief Cantidad de munici�n contenida en la caja.
     *
     * Inicialmente, cada caja contiene 15 unidades de munici�n.
     */
    int ammoCount;

    /**
     * @brief Acci�n para recoger la caja de munici�n.
     *
     * Este m�todo sobrescribe el comportamiento de Pickup. Si la caja
     * de munici�n es recogida por el jugador, la cantidad de munici�n
     * se transfiere al arma actual del jugador.
     *
     * true si la munici�n fue recogida exitosamente, false en caso contrario.
     */
    bool pickup() override;

    /**
     * @brief Constructor de la clase AmmoBox.
     *
     * Inicializa una caja de munici�n en la posici�n especificada y asigna
     * la cantidad de munici�n por defecto (15 unidades).
     *
     * @param pos Posici�n inicial de la caja en el espacio 2D.
     */

    AmmoBox(Point2D pos);
};
