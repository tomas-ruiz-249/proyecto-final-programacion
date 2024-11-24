#pragma once
#include "Point2D.h"
#include "Map.h"

/**
 * @class Entity
 * @brief Clase base para representar entidades dentro de un mapa en el juego.
 *
 * La clase `Entity` sirve como base para todos los objetos del juego que pueden
 * interactuar con un mapa, moverse y tener propiedades como posici�n, velocidad y salud.
 * Es una clase abstracta que define m�todos que las clases derivadas deben implementar.
 */
class Entity {
public:
    /**
     * @brief Indica si la entidad est� herida.
     */
    bool hurt;

    /**
     * @brief Posici�n de la entidad en el mapa.
     */
    Point2D position;

    /**
     * @brief �ngulo de orientaci�n de la entidad en grados.
     */
    double angle;

    /**
     * @brief Velocidad de movimiento de la entidad.
     */
    double speed;

    /**
     * @brief Obtiene la salud actual de la entidad.
     * @return Salud de la entidad como un entero.
     */
    int getHealth();

    /**
     * @brief Acci�n principal que realiza la entidad en el mapa.
     * @param map Referencia al mapa donde act�a la entidad.
     *
     * Este m�todo debe ser implementado por las clases derivadas
     * para definir comportamientos espec�ficos.
     */
    virtual void act(Map& map) = 0;

    /**
     * @brief Mueve la entidad dentro del mapa.
     * @param map Referencia al mapa donde se mueve la entidad.
     *
     * Este m�todo debe ser implementado por las clases derivadas
     * para definir c�mo se mueve la entidad en el mapa.
     */
    virtual void move(Map& map) = 0;

    /**
     * @brief Aplica da�o a la entidad.
     * @param damage Cantidad de da�o a aplicar.
     *
     * Este m�todo debe ser implementado por las clases derivadas
     * para manejar la l�gica de reducci�n de salud o efectos secundarios.
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Realiza un ataque.
     *
     * Este m�todo debe ser implementado por las clases derivadas
     * para definir la l�gica de ataque de la entidad.
     */
    virtual void attack() = 0;

    /**
     * @brief Verifica si la entidad est� viva.
     * @return `true` si la salud de la entidad es mayor a 0, `false` en caso contrario.
     */
    virtual bool isAlive();

    /**
     * @brief Constructor por defecto de la clase Entity.
     *
     * Inicializa la posici�n en (0, 0), velocidad en 0.0 y �ngulo en 0.
     */
    Entity();

    /**
     * @brief Constructor que inicializa la salud de la entidad.
     * @param health Salud inicial de la entidad.
     *
     * Adem�s, inicializa la posici�n en (0, 0), velocidad en 0.0 y �ngulo en 0.
     */
    Entity(unsigned int health);

protected:
    /**
     * @brief Salud actual de la entidad.
     *
     * Solo accesible desde la clase base y clases derivadas.
     */
    int health;
};
