#pragma once

/**
 * @struct Point2D
 * @brief Representa un punto en un espacio bidimensional con coordenadas de tipo `double`.
 *
 * Esta estructura se utiliza para almacenar y manipular puntos con valores decimales
 * en un sistema de coordenadas 2D.
 */
typedef struct Point2D {
	double x; /**< Coordenada X del punto. */
	double y; /**< Coordenada Y del punto. */
} Point2D;

/**
 * @struct IPoint2D
 * @brief Representa un punto en un espacio bidimensional con coordenadas de tipo entero sin signo.
 *
 * Esta estructura se utiliza principalmente para trabajar con índices o coordenadas discretas
 * en sistemas 2D, como en mapas o matrices.
 */
typedef struct IPoint2D {
	unsigned int x; /**< Coordenada X del punto como un entero sin signo. */
	unsigned int y; /**< Coordenada Y del punto como un entero sin signo. */
} IPoint2D;