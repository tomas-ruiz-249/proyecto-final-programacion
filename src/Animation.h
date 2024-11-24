#pragma once
#include <raylib.h>

/**
 * @class Animation
 * @brief Clase que representa una animación basada en cuadros (frames).
 *
 * Esta clase encapsula información y métodos relacionados con la
 * reproducción de animaciones, como el número de cuadros, velocidad,
 * y el área de textura para cada cuadro.
 */
class Animation {
public:
    /**
     * @brief Número total de cuadros en la animación.
     */
    int numFrames;

    /**
     * @brief Temporizador interno para controlar el cambio de cuadros.
     */
    double frameTimer;

    /**
     * @brief Velocidad de la animación en segundos por cuadro.
     */
    double animationSpeed;

    /**
     * @brief Área de la textura que contiene los cuadros de la animación.
     */
    Rectangle textureArea;

    /**
     * @brief Posición donde se renderiza la animación en la ventana.
     */
    Rectangle positionOnWindow;

    /**
     * @brief Textura que contiene los cuadros de la animación.
     */
    Texture texture;

    /**
     * @brief Indica si la animación debe detenerse.
     */
    bool stop;

    /**
     * @brief Devuelve el cuadro actual de la animación.
     * @return Un entero que representa el índice del cuadro actual.
     */
    int getCurrentFrame();

    /**
     * @brief Verifica si la animación ha llegado al último cuadro.
     * @return true si la animación ha terminado, false en caso contrario.
     */
    bool isAnimationDone();

    /**
     * @brief Reinicia la animación al primer cuadro.
     */
    void resetAnimation();

    /**
     * @brief Avanza al siguiente cuadro en la animación.
     *
     * Si la animación llega al último cuadro, vuelve al primero.
     */
    void nextFrame();

private:
    /**
     * @brief Cuadro actual que se está reproduciendo.
     */
    int currentFrame;
};

