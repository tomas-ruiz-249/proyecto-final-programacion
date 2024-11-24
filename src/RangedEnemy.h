#pragma once
#include "Enemy.h"
#include "Item.h"
#include "Projectile.h"

/**
 * @class RangedEnemy
 * @brief Representa un enemigo que ataca a distancia utilizando proyectiles.
 *
 * Esta clase hereda de `Enemy` y añade comportamiento específico para enemigos
 * que utilizan proyectiles en sus ataques. Gestiona acciones como movimiento,
 * ataques a distancia, y la interacción con los proyectiles disparados.
 */
class RangedEnemy : public Enemy {
public:
    /**
     * @brief Realiza las acciones principales del enemigo en cada frame.
     *
     * Llama a las acciones de la clase base y verifica colisiones de los proyectiles.
     *
     * @param map Referencia al mapa actual, usado para calcular interacciones.
     */
    void act(Map& map) override;

    /**
     * @brief Realiza un ataque a distancia disparando un proyectil.
     *
     * Si el enemigo está en posición de atacar, dispara un proyectil y reproduce
     * un efecto de sonido. Gestiona los tiempos de recarga del ataque.
     */
    void attack() override;

    /**
     * @brief Mueve al enemigo si no está atacando.
     *
     * Llama al método de movimiento de la clase base mientras el enemigo no esté en modo ataque.
     *
     * @param map Referencia al mapa actual, usado para verificar colisiones y caminos.
     */
    void move(Map& map) override;

    /**
     * @brief Aplica daño al enemigo.
     *
     * Reduce la vida del enemigo, reproduce un sonido de daño y, si el enemigo muere,
     * reproduce un sonido de muerte.
     *
     * @param damage Cantidad de daño recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Obtiene la lista de proyectiles disparados por el enemigo.
     *
     * @return Un vector de punteros a objetos `Projectile`.
     */
    std::vector<Projectile*> getProjectiles();

    /**
     * @brief Constructor de la clase RangedEnemy.
     *
     * Inicializa al enemigo con una posición específica y valores predeterminados
     * para velocidad, temporizadores de ataque y estados iniciales.
     *
     * @param position La posición inicial del enemigo en el mapa.
     */
    RangedEnemy(Point2D position);

private:
    std::vector<Projectile*> projectiles; /**< Lista de proyectiles disparados por el enemigo. */
    bool attacking;                       /**< Indica si el enemigo está en modo ataque. */
    double attackTimer;                   /**< Temporizador para el manejo del tiempo entre ataques. */
    double attackCoolDown;                /**< Tiempo de enfriamiento entre ataques en segundos. */

    /**
     * @brief Verifica colisiones de los proyectiles disparados por el enemigo.
     *
     * Gestiona las colisiones de los proyectiles con el jugador o el entorno,
     * eliminando los proyectiles que ya no son válidos.
     */
    void checkForProjectileColision();
};
