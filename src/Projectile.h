#pragma once
#include "Point2D.h"
#include "Animated.h"

/**
 * @class Projectile
 * @brief Representa un proyectil en el juego, con capacidades de movimiento, colisión y daño.
 *
 * La clase `Projectile` gestiona las propiedades y el comportamiento de los proyectiles
 * en el juego, incluyendo su posición, velocidad, trayectoria, y colisiones con objetos
 * como el jugador y las paredes.
 */
class Projectile {
public:
    /**
     * @brief Constructor de la clase Projectile.
     *
     * @param pos La posición inicial del proyectil.
     * @param ang El ángulo de movimiento del proyectil en radianes.
     * @param damage La cantidad de daño que inflige el proyectil al impactar.
     */
    Projectile(Point2D pos, double ang, int damage);

    /**
     * @brief Maneja el movimiento del proyectil y verifica colisiones.
     *
     * Este método actualiza la posición del proyectil y detecta si ha colisionado
     * con el jugador, una pared o si ha excedido su tiempo límite.
     *
     * @return `true` si el proyectil colisiona o expira; `false` en caso contrario.
     */
    bool shoot();

    /**
     * @brief Obtiene la posición actual del proyectil.
     *
     * @return La posición actual como un objeto `Point2D`.
     */
    Point2D getPosition();

    /**
     * @brief Sprite animado que representa al proyectil.
     *
     * Este sprite contiene las animaciones visuales del proyectil.
     */
    Animated* sprite;

private:
    int damage;             /**< Daño que inflige el proyectil al impactar. */
    double timeLimit;       /**< Tiempo máximo de vida del proyectil en segundos. */
    double timer;           /**< Temporizador que mide el tiempo de existencia del proyectil. */
    double speed;           /**< Velocidad de movimiento del proyectil. */
    double angle;           /**< Ángulo de movimiento del proyectil en radianes. */
    Point2D position;       /**< Posición actual del proyectil. */
};
