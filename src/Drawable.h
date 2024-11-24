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
 * todos los objetos que pueden ser dibujados en la pantalla. Incluye la posici�n,
 * �rea de textura, escala y profundidad.
 */

class Drawable {
public:
    /**
     * @brief �rea de la textura que ser� renderizada.
     *
     * Define una porci�n de la textura que se utilizar� para dibujar el sprite.
     */
    Rectangle textureArea;

    /**
     * @brief �rea de la ventana donde se dibujar� el objeto.
     *
     * Representa la posici�n y dimensiones en p�xeles del objeto en la pantalla.
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
     * Permite modificar el tama�o del objeto en funci�n de su distancia o contexto.
     */
    double scale;

    /**
     * @brief Desplazamiento vertical del objeto en la pantalla.
     *
     * �til para ajustar la posici�n de renderizado en relaci�n con otros elementos.
     */
    double shift;

    /**
     * @brief Posici�n 2D del objeto en el mundo.
     */
    Point2D position;

    /**
     * @brief Indica si el objeto est� en el centro de la pantalla.
     *
     * Este atributo se utiliza para verificar si el objeto se encuentra
     * en el campo de visi�n principal del jugador.
     */
    bool isOnScreenCenter;

    /**
     * @brief Textura asociada al objeto.
     */
    Texture tex;

    /**
     * @brief Calcula la distancia entre el objeto y el jugador.
     *
     * Este m�todo determina la distancia euclidiana entre la posici�n
     * del objeto y la posici�n actual del jugador.
     *
     * @param position Posici�n del objeto en el mundo.
     * @param player Referencia al jugador.
     * @return Distancia en unidades del mundo.
     */
    double getDistanceFromPlayer(Point2D position, Player player);

    /**
     * @brief Destructor virtual para poder usar dynamic_cast<>().
     */
    virtual ~Drawable() = default;
};

