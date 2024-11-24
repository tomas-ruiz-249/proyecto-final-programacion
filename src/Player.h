#pragma once
#include "Entity.h"
#include "Weapon.h"

/**
 * @class Player
 * @brief Representa al jugador controlado por el usuario en el juego.
 *
 * La clase `Player` hereda de `Entity` y encapsula todas las funcionalidades relacionadas con el
 * movimiento, ataque, recibir daño y otras interacciones del jugador dentro del juego.
 * También administra su propia arma y estados como salud y sensibilidad.
 */
class Player : public Entity {
public:
    /// Arma actualmente equipada por el jugador.
    Weapon* weapon;

    /// Indica si el jugador disparó recientemente.
    bool justShot;

    /**
     * @brief Realiza las acciones principales del jugador.
     *
     * Comprueba si el jugador está vivo para realizar movimientos y ataques.
     * También actualiza el temporizador de daño recibido.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void act(Map& map) override;

    /**
     * @brief Gestiona el movimiento del jugador en el mapa.
     *
     * Permite el movimiento en función de las entradas del teclado y ajusta la posición
     * del jugador en el mapa. También permite interactuar con puertas cercanas.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void move(Map& map) override;

    /**
     * @brief Maneja el daño recibido por el jugador.
     *
     * Reduce la salud del jugador si el temporizador de daño permite recibir otro golpe.
     * Reproduce un sonido al recibir daño.
     *
     * @param damage Cantidad de daño recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Permite al jugador atacar con su arma.
     *
     * Si el arma tiene munición y el jugador intenta disparar, realiza un disparo.
     * Si no hay munición, reproduce un sonido de recarga.
     */
    void attack() override;

    /**
     * @brief Cura al jugador utilizando puntos de vida.
     *
     * Si la salud del jugador es menor que el máximo, incrementa la salud
     * hasta un máximo permitido y reproduce un sonido de curación.
     *
     * @param healthPoints Puntos de salud para curar.
     * @return `true` si la curación fue exitosa, `false` en caso contrario.
     */
    bool heal(int healthPoints);

    /**
     * @brief Restaura al jugador a su estado inicial.
     *
     * Restablece la salud máxima, posición inicial y munición del arma.
     */
    void reset();

    /**
     * @brief Establece la sensibilidad del jugador al mover la cámara.
     *
     * @param sensibility Nueva sensibilidad.
     */
    void setSensibility(double sensibility);

    /**
     * @brief Obtiene la sensibilidad actual del jugador.
     *
     * @return Sensibilidad del jugador.
     */
    double getSensibility();

    /**
     * @brief Devuelve el valor máximo de salud del jugador.
     *
     * @return Salud máxima.
     */
    int getMaxHealth();

    /**
     * @brief Obtiene la instancia única del jugador.
     *
     * Implementa el patrón Singleton para garantizar que solo exista una instancia de `Player`.
     *
     * @return Puntero a la instancia única de `Player`.
     */
    static Player* getInstance();

    /**
     * @brief Clase amiga para permitir que `HealthBox` acceda a los miembros privados de `Player`.
     */
    friend class HealthBox;

private:
    /// Salud máxima del jugador.
    int maxHealth;

    /// Sensibilidad de la cámara al mover el mouse.
    double sensibility;

    /// Temporizador para gestionar el intervalo entre daños consecutivos.
    double hurtTimer;

    /// Instancia única de `Player` para el patrón Singleton.
    static Player* player;

    /**
     * @brief Constructor privado para implementar el patrón Singleton.
     */
    Player();
};
