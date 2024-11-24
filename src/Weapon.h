#pragma once
#include "Animated.h"

/**
 * @class Weapon
 * @brief Representa un arma en el juego, con funcionalidades de disparo, recarga y manejo de munición.
 *
 * La clase Weapon encapsula la lógica relacionada con el comportamiento de un arma,
 * como disparar, verificar si puede disparar, y recargar munición. También define
 * atributos básicos como daño, alcance y estado de recarga.
 */
class Weapon {
public:
    /**
     * @brief Constructor de la clase Weapon.
     *
     * Inicializa los atributos del arma con valores predeterminados,
     * incluyendo el sprite, daño, alcance, munición máxima y el estado inicial.
     */
    Weapon();

    /**
     * @brief Dispara el arma si hay munición disponible.
     *
     * Reproduce un sonido de disparo y reduce la munición disponible.
     * Cambia el estado del arma a "recargando".
     */
    void shoot();

    /**
     * @brief Verifica si el arma está lista para disparar.
     *
     * Determina si el arma puede disparar basándose en el estado de recarga
     * y la cantidad de munición disponible.
     * @return `true` si el arma puede disparar, `false` en caso contrario.
     */
    bool canShoot();

    /**
     * @brief Recarga munición al arma.
     *
     * Añade una cantidad específica de munición al arma, sin exceder el límite máximo.
     * Reproduce un sonido de recarga al completarse.
     * @param refill Cantidad de munición a recargar.
     * @return `true` si la recarga fue exitosa, `false` si el arma ya tiene munición completa.
     */
    bool refillAmmo(int refill);

    /**
     * @brief Obtiene el daño del arma.
     * @return El valor del daño que inflige el arma por disparo.
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
     * Representa la animación visual asociada al arma.
     */
    Animated* sprite;

    /**
     * @brief Declara amistad con Canvas.
     *
     * Canvas tiene acceso a los atributos y métodos privados del arma.
     */
    friend class Canvas;

    /**
     * @brief Declara amistad con AmmoBox.
     *
     * AmmoBox tiene acceso a los atributos y métodos privados del arma.
     */
    friend class AmmoBox;

private:
    int damage; ///< Daño que inflige el arma por disparo.
    int range; ///< Alcance efectivo del arma.
    unsigned int ammoCount; ///< Munición actual disponible en el arma.
    bool reloading; ///< Indica si el arma está en proceso de recarga.
    int maxAmmo; ///< Cantidad máxima de munición que puede tener el arma.
};
