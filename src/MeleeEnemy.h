#pragma once
#include "Enemy.h"

/**
 * @class MeleeEnemy
 * @brief Representa a un enemigo que ataca cuerpo a cuerpo en el juego.
 *
 * `MeleeEnemy` es una clase derivada de `Enemy` que implementa un comportamiento
 * específico de ataque cuerpo a cuerpo y la respuesta al recibir daño.
 */
class MeleeEnemy : public Enemy {
public:
    /**
     * @brief Realiza un ataque cuerpo a cuerpo al jugador.
     *
     * Si el jugador está lo suficientemente cerca (distancia <= 0.5), está vivo y no está
     * en estado de "herido", el enemigo realiza un ataque que reproduce un sonido y
     * aplica daño al jugador.
     */
    void attack() override;

    /**
     * @brief Maneja el daño recibido por el enemigo.
     *
     * Reduce la vida del enemigo en función del daño recibido. Si el enemigo sigue con vida,
     * se reproduce un sonido de "herido". Si muere, se reproduce un sonido de "muerte".
     *
     * @param damage Cantidad de daño recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Constructor de la clase `MeleeEnemy`.
     *
     * @param position Posición inicial del enemigo (tipo `Point2D`).
     *
     * Inicializa la posición y configura la velocidad del enemigo cuerpo a cuerpo.
     */
    MeleeEnemy(Point2D position);
};
