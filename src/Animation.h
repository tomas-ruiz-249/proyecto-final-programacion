#pragma once
#include <raylib.h>

/**
 * @class Animation
 * @brief Clase que representa una animaci�n basada en cuadros (frames).
 *
 * Esta clase encapsula informaci�n y m�todos relacionados con la
 * reproducci�n de animaciones, como el n�mero de cuadros, velocidad,
 * y el �rea de textura para cada cuadro.
 */

class Animation {
public:
    /**
     * @brief N�mero total de cuadros en la animaci�n.
     */
    int numFrames;

    /**
     * @brief Temporizador interno para controlar el cambio de cuadros.
     */
    double frameTimer;

    /**
     * @brief Velocidad de la animaci�n en segundos por cuadro.
     */
    double animationSpeed;

    /**
     * @brief �rea de la textura que contiene los cuadros de la animaci�n.
     */
    Rectangle textureArea;

    /**
     * @brief Posici�n donde se renderiza la animaci�n en la ventana.
     */
    Rectangle positionOnWindow;

    /**
     * @brief Textura que contiene los cuadros de la animaci�n.
     */
    Texture texture;

    /**
     * @brief Indica si la animaci�n debe detenerse.
     */
    bool stop;

    /**
     * @brief Devuelve el cuadro actual de la animaci�n.
     * @return Un entero que representa el �ndice del cuadro actual.
     */
    int getCurrentFrame();

    /**
     * @brief Verifica si la animaci�n ha llegado al �ltimo cuadro.
     * @return true si la animaci�n ha terminado, false en caso contrario.
     */

    bool isAnimationDone();

    /**
     * @brief Reinicia la animaci�n al primer cuadro.
     */

    void resetAnimation();

    /**
     * @brief Avanza al siguiente cuadro en la animaci�n.
     *
     * Si la animaci�n llega al �ltimo cuadro, vuelve al primero.
     */

    void nextFrame();

private:
    /**
     * @brief Cuadro actual que se est� reproduciendo.
     */
    int currentFrame;
};

