#pragma once

#include "Entity.h"
#include "Animated.h"
#include "Enumerations.h"

/**
 * @class Enemy
 * @brief Representa un enemigo dentro del juego.
 *
 * La clase `Enemy` extiende de `Entity` y define el comportamiento específico
 * de los enemigos, incluyendo su movimiento, ataque y respuesta a daño.
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
     * Utiliza la enumeración `EnemyType` para categorizar el tipo de enemigo.
     */
    EnemyType type;

    /**
     * @brief Realiza las acciones del enemigo.
     *
     * Este método determina el comportamiento del enemigo durante su turno,
     * como moverse hacia el jugador o atacar.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void act(Map& map) override;

    /**
     * @brief Aplica daño al enemigo.
     *
     * Este método reduce la salud del enemigo y marca si está herido.
     *
     * @param damage Cantidad de daño recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Mueve al enemigo en dirección al jugador.
     *
     * Utiliza cálculos basados en el raycasting para determinar si el jugador
     * está a la vista y, en ese caso, mueve al enemigo hacia él.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void move(Map& map) override;

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa al enemigo con valores predeterminados de salud y daño.
     */
    Enemy();

    /**
     * @brief Constructor que inicializa los atributos principales.
     *
     * @param health Salud inicial del enemigo.
     * @param damage Daño que inflige el enemigo.
     */
    Enemy(int health, int damage);

protected:
    /**
     * @brief Daño que puede infligir el enemigo al jugador.
     */
    int damage;
};
