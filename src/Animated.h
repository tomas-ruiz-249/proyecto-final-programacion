#pragma once
#include "Drawable.h"
/**
 * @class Animated
 * @brief Clase que representa un objeto dibujable con animaciones.
 *
 * La clase `Animated` hereda de `Drawable` y agrega capacidades
 * para manejar múltiples animaciones. Cada instancia puede contener
 * una lista de animaciones y un índice que indica la animación actual.
 */
class Animated : public Drawable {
public:
    /**
     * @brief Índice de la animación actualmente activa.
     */
    int animationIndex;

    /**
     * @brief Lista de animaciones asociadas a este objeto.
     */
    std::vector<Animation> animations;
};
