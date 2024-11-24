#pragma once
#include "Point2D.h"
#include "Map.h"

/**
 * @class Entity
 * @brief Clase base para representar entidades dentro de un mapa en el juego.
 *
 * La clase `Entity` sirve como base para todos los objetos del juego que pueden
 * interactuar con un mapa, moverse y tener propiedades como posición, velocidad y salud.
 * Es una clase abstracta que define métodos que las clases derivadas deben implementar.
 */
class Entity {
public:
    /**
     * @brief Indica si la entidad está herida.
     */
    bool hurt;

    /**
     * @brief Posición de la entidad en el mapa.
     */
    Point2D position;

    /**
     * @brief Ángulo de orientación de la entidad en grados.
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
     * @brief Acción principal que realiza la entidad en el mapa.
     * @param map Referencia al mapa donde actúa la entidad.
     *
     * Este método debe ser implementado por las clases derivadas
     * para definir comportamientos específicos.
     */
    virtual void act(Map& map) = 0;

    /**
     * @brief Mueve la entidad dentro del mapa.
     * @param map Referencia al mapa donde se mueve la entidad.
     *
     * Este método debe ser implementado por las clases derivadas
     * para definir cómo se mueve la entidad en el mapa.
     */
    virtual void move(Map& map) = 0;

    /**
     * @brief Aplica daño a la entidad.
     * @param damage Cantidad de daño a aplicar.
     *
     * Este método debe ser implementado por las clases derivadas
     * para manejar la lógica de reducción de salud o efectos secundarios.
     */
    virtual void takeDamage(int damage) = 0;

    /**
     * @brief Realiza un ataque.
     *
     * Este método debe ser implementado por las clases derivadas
     * para definir la lógica de ataque de la entidad.
     */
    virtual void attack() = 0;

    /**
     * @brief Verifica si la entidad está viva.
     * @return `true` si la salud de la entidad es mayor a 0, `false` en caso contrario.
     */
    virtual bool isAlive();

    /**
     * @brief Constructor por defecto de la clase Entity.
     *
     * Inicializa la posición en (0, 0), velocidad en 0.0 y ángulo en 0.
     */
    Entity();

    /**
     * @brief Constructor que inicializa la salud de la entidad.
     * @param health Salud inicial de la entidad.
     *
     * Además, inicializa la posición en (0, 0), velocidad en 0.0 y ángulo en 0.
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
