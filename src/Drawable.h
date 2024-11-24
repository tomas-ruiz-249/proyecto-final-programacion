#pragma once
#include <raylib.h>
#include <vector>
#include "Animation.h"
#include "Point2D.h"
#pragma once

#include <raylib.h>
#include <vector>
#include "Animation.h"
#include "Point2D.h"

class Player;

/**
 * @class Drawable
 * @brief Clase base para objetos renderizables en el juego.
 *
 * La clase `Drawable` encapsula propiedades y comportamientos comunes para
 * todos los objetos que pueden ser dibujados en la pantalla. Incluye la posición,
 * área de textura, escala y profundidad.
 */
class Drawable {
public:
    /**
     * @brief Área de la textura que será renderizada.
     *
     * Define una porción de la textura que se utilizará para dibujar el sprite.
     */
    Rectangle textureArea;

    /**
     * @brief Área de la ventana donde se dibujará el objeto.
     *
     * Representa la posición y dimensiones en píxeles del objeto en la pantalla.
     */
    Rectangle positionOnWindow;

    /**
     * @brief Distancia del objeto al jugador.
     *
     * Se utiliza para calcular la profundidad relativa al jugador y
     * determinar el orden de renderizado.
     */
    double depth;

    /**
     * @brief Escala del objeto en la pantalla.
     *
     * Permite modificar el tamaño del objeto en función de su distancia o contexto.
     */
    double scale;

    /**
     * @brief Desplazamiento vertical del objeto en la pantalla.
     *
     * Útil para ajustar la posición de renderizado en relación con otros elementos.
     */
    double shift;

    /**
     * @brief Posición 2D del objeto en el mundo.
     */
    Point2D position;

    /**
     * @brief Indica si el objeto está en el centro de la pantalla.
     *
     * Este atributo se utiliza para verificar si el objeto se encuentra
     * en el campo de visión principal del jugador.
     */
    bool isOnScreenCenter;

    /**
     * @brief Textura asociada al objeto.
     */
    Texture tex;

    /**
     * @brief Calcula la distancia entre el objeto y el jugador.
     *
     * Este método determina la distancia euclidiana entre la posición
     * del objeto y la posición actual del jugador.
     *
     * @param position Posición del objeto en el mundo.
     * @param player Referencia al jugador.
     * @return Distancia en unidades del mundo.
     */
    double getDistanceFromPlayer(Point2D position, Player player);

    /**
     * @brief Destructor virtual para asegurar una limpieza adecuada.
     */
    virtual ~Drawable() = default;
};

