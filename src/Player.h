#pragma once
#include "Entity.h"
#include "Weapon.h"

/**
 * @class Player
 * @brief Representa al jugador controlado por el usuario en el juego.
 *
 * La clase `Player` hereda de `Entity` y encapsula todas las funcionalidades relacionadas con el
 * movimiento, ataque, recibir da�o y otras interacciones del jugador dentro del juego.
 * Tambi�n administra su propia arma y estados como salud y sensibilidad.
 */
class Player : public Entity {
public:
    /// Arma actualmente equipada por el jugador.
    Weapon* weapon;

    /// Indica si el jugador dispar� recientemente.
    bool justShot;

    /**
     * @brief Realiza las acciones principales del jugador.
     *
     * Comprueba si el jugador est� vivo para realizar movimientos y ataques.
     * Tambi�n actualiza el temporizador de da�o recibido.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void act(Map& map) override;

    /**
     * @brief Gestiona el movimiento del jugador en el mapa.
     *
     * Permite el movimiento en funci�n de las entradas del teclado y ajusta la posici�n
     * del jugador en el mapa. Tambi�n permite interactuar con puertas cercanas.
     *
     * @param map Referencia al mapa actual del juego.
     */
    void move(Map& map) override;

    /**
     * @brief Maneja el da�o recibido por el jugador.
     *
     * Reduce la salud del jugador si el temporizador de da�o permite recibir otro golpe.
     * Reproduce un sonido al recibir da�o.
     *
     * @param damage Cantidad de da�o recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Permite al jugador atacar con su arma.
     *
     * Si el arma tiene munici�n y el jugador intenta disparar, realiza un disparo.
     * Si no hay munici�n, reproduce un sonido de recarga.
     */
    void attack() override;

    /**
     * @brief Cura al jugador utilizando puntos de vida.
     *
     * Si la salud del jugador es menor que el m�ximo, incrementa la salud
     * hasta un m�ximo permitido y reproduce un sonido de curaci�n.
     *
     * @param healthPoints Puntos de salud para curar.
     * @return `true` si la curaci�n fue exitosa, `false` en caso contrario.
     */
    bool heal(int healthPoints);

    /**
     * @brief Restaura al jugador a su estado inicial.
     *
     * Restablece la salud m�xima, posici�n inicial y munici�n del arma.
     */
    void reset();

    /**
     * @brief Establece la sensibilidad del jugador al mover la c�mara.
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
     * @brief Devuelve el valor m�ximo de salud del jugador.
     *
     * @return Salud m�xima.
     */
    int getMaxHealth();

    /**
     * @brief Obtiene la instancia �nica del jugador.
     *
     * Implementa el patr�n Singleton para garantizar que solo exista una instancia de `Player`.
     *
     * @return Puntero a la instancia �nica de `Player`.
     */
    static Player* getInstance();

private:
    /// Salud m�xima del jugador.
    int maxHealth;

    /// Sensibilidad de la c�mara al mover el mouse.
    double sensibility;

    /// Temporizador para gestionar el intervalo entre da�os consecutivos.
    double hurtTimer;

    /// Instancia �nica de `Player` para el patr�n Singleton.
    static Player* instance;
    
    /**
     * @brief Constructor privado para implementar el patr�n Singleton.
     */
    Player();
};
