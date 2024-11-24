#pragma once

#include "Entity.h"
#include "Animated.h"
#include "Enumerations.h"

/**
 * @class Enemy
 * @brief Representa un enemigo dentro del juego.
 *
 * La clase `Enemy` extiende de `Entity` y define el comportamiento espec�fico
 * de los enemigos, incluyendo su movimiento, ataque y respuesta a da�o.
 */
class Enemy : public Entity {
public:
    /**
     * @brief Sprite animado que representa al enemigo en pantalla.
     */
    Animated* sprite;

    /**
     * @brief Tipo del enemigo.
     *
     * Utiliza la enumeraci�n `EnemyType` para categorizar el tipo de enemigo.
     */
    EnemyType type;

    /**
     * @brief Realiza las acciones del enemigo.
     *
     * Este m�todo determina el comportamiento del enemigo durante su turno,
     * como moverse hacia el jugador o atacar.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void act(Map& map) override;

    /**
     * @brief Aplica da�o al enemigo.
     *
     * Este m�todo reduce la salud del enemigo y marca si est� herido.
     *
     * @param damage Cantidad de da�o recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Mueve al enemigo en direcci�n al jugador.
     *
     * Utiliza c�lculos basados en el raycasting para determinar si el jugador
     * est� a la vista y, en ese caso, mueve al enemigo hacia �l.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void move(Map& map) override;

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa al enemigo con valores predeterminados de salud y da�o.
     */
    Enemy();

    /**
     * @brief Constructor que inicializa los atributos principales.
     *
     * @param health Salud inicial del enemigo.
     * @param damage Da�o que inflige el enemigo.
     */
    Enemy(int health, int damage);

protected:
    /**
     * @brief Da�o que puede infligir el enemigo al jugador.
     */

    int damage;
};
