#pragma once
#include "Animated.h"

/**
 * @class Weapon
 * @brief Representa un arma en el juego, con funcionalidades de disparo, recarga y manejo de munici�n.
 *
 * La clase Weapon encapsula la l�gica relacionada con el comportamiento de un arma,
 * como disparar, verificar si puede disparar, y recargar munici�n. Tambi�n define
 * atributos b�sicos como da�o, alcance y estado de recarga.
 */

class Weapon {
public:
    /**
     * @brief Constructor de la clase Weapon.
     *
     * Inicializa los atributos del arma con valores predeterminados,
     * incluyendo el sprite, da�o, alcance, munici�n m�xima y el estado inicial.
     */
    Weapon();

    /**
     * @brief Dispara el arma si hay munici�n disponible.
     *
     * Reproduce un sonido de disparo y reduce la munici�n disponible.
     * Cambia el estado del arma a "recargando".
     */
    void shoot();

    /**
     * @brief Verifica si el arma est� lista para disparar.
     *
     * Determina si el arma puede disparar bas�ndose en el estado de recarga
     * y la cantidad de munici�n disponible.
     * @return `true` si el arma puede disparar, `false` en caso contrario.
     */
    bool canShoot();

    /**
     * @brief Recarga munici�n al arma.
     *
     * A�ade una cantidad espec�fica de munici�n al arma, sin exceder el l�mite m�ximo.
     * Reproduce un sonido de recarga al completarse.
     * @param refill Cantidad de munici�n a recargar.
     * @return `true` si la recarga fue exitosa, `false` si el arma ya tiene munici�n completa.
     */
    bool refillAmmo(int refill);

    /**
     * @brief Obtiene el da�o del arma.
     * @return El valor del da�o que inflige el arma por disparo.
     */
    int getDamage();

    /**
     * @brief Obtiene el alcance del arma.
     * @return El rango efectivo del arma.
     */
    int getRange();

    /**
     * @brief Sprite animado del arma.
     *
     * Representa la animaci�n visual asociada al arma.
     */
    Animated* sprite;

    /**
     * @brief Declara amistad con Canvas.
     *
     * Canvas tiene acceso a los atributos y m�todos privados del arma.
     */
    friend class Canvas;

    /**
     * @brief Declara amistad con AmmoBox.
     *
     * AmmoBox tiene acceso a los atributos y m�todos privados del arma.
     */
    friend class AmmoBox;

private:
    int damage; ///< Da�o que inflige el arma por disparo.
    int range; ///< Alcance efectivo del arma.
    unsigned int ammoCount; ///< Munici�n actual disponible en el arma.
    bool reloading; ///< Indica si el arma est� en proceso de recarga.
    int maxAmmo; ///< Cantidad m�xima de munici�n que puede tener el arma.
};
