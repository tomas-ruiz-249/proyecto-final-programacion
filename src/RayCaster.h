#pragma once
#include <vector>
#pragma once
#include <vector>
#include "Map.h"
#include "Enumerations.h"
#include "Player.h"
#include "Drawable.h"

/**
 * @struct RayCastResult
 * @brief Representa el resultado de un cálculo de raycasting.
 *
 * Contiene información sobre el punto de impacto del rayo, la textura impactada,
 * y datos necesarios para el cálculo de proyección y renderizado.
 */
struct RayCastResult : public Drawable {
    Point2D hitCoordinates; /**< Coordenadas del punto de impacto del rayo. */
    float horizontalTextureOffset; /**< Desplazamiento horizontal para aplicar la textura en la pared. */
    int index; /**< Índice del rayo en la lista de rayos lanzados. */
    WallType wall; /**< Tipo de pared impactada. */
    double cos; /**< Valor del coseno del ángulo del rayo. */
    double sin; /**< Valor del seno del ángulo del rayo. */
};

/**
 * @class RayCaster
 * @brief Clase responsable de gestionar el raycasting en el motor del juego.
 *
 * El `RayCaster` calcula trayectorias de rayos desde un origen, detecta colisiones con paredes
 * y proporciona información necesaria para el renderizado de vistas en primera persona.
 */
class RayCaster {
public:
    /**
     * @brief Realiza un raycasting desde una posición específica.
     *
     * Calcula la intersección más cercana del rayo con las paredes del mapa en la dirección dada.
     *
     * @param angle Ángulo del rayo en radianes.
     * @param position Posición inicial desde donde se lanza el rayo.
     * @param map Referencia al mapa donde se realiza el raycasting.
     * @return Una estructura `RayCastResult` con la información del impacto del rayo.
     */
    RayCastResult rayCast(double angle, Point2D position, Map& map);

    /**
     * @brief Obtiene todos los rayos en un rango de ángulo.
     *
     * Lanza múltiples rayos, calcula sus colisiones y ajusta las profundidades
     * para eliminar distorsión por proyección en ángulo.
     *
     * @param rayAngle Ángulo inicial del rayo en radianes.
     * @param player Referencia al jugador desde donde se lanza el raycasting.
     * @param map Referencia al mapa donde se realiza el raycasting.
     * @return Un vector de `RayCastResult` con información de cada rayo lanzado.
     */
    std::vector<RayCastResult> getAllRays(double rayAngle, Player player, Map map);

    /**
     * @brief Obtiene el ángulo entre rayos consecutivos.
     *
     * @return El valor del delta del ángulo en radianes.
     */
    double getDeltaAngle();

    /**
     * @brief Obtiene el número total de rayos lanzados.
     *
     * @return El número de rayos.
     */
    double getNumRays();

    /**
     * @brief Limpia la lista de rayos almacenados.
     *
     * Vacía el vector de resultados de raycasting.
     */
    void clearRays();

    /**
     * @brief Constructor parametrizado de `RayCaster`.
     *
     * Inicializa la clase con un número de rayos y un delta de ángulo específico.
     *
     * @param numRays Número total de rayos a lanzar.
     * @param deltaAngle Ángulo entre rayos consecutivos en radianes.
     */
    RayCaster(int numRays, double deltaAngle);

    /**
     * @brief Constructor por defecto de `RayCaster`.
     */
    RayCaster();

private:
    std::vector<RayCastResult> rays; /**< Vector de resultados de raycasting. */
    int numRays; /**< Número total de rayos a lanzar. */
    double deltaAngle; /**< Ángulo entre rayos consecutivos en radianes. */

    /**
     * @brief Calcula la intersección más cercana en el eje X.
     *
     * Determina la primera celda del mapa en el eje X que intersecta el rayo.
     *
     * @param angle Ángulo del rayo en radianes.
     * @param position Posición inicial del rayo.
     * @param xNearestLength Distancia desde la posición inicial al punto de impacto en el eje X.
     * @return Coordenadas del punto de impacto en el eje X.
     */
    Point2D calculateXNearest(double angle, Point2D position, double& xNearestLength);

    /**
     * @brief Calcula la intersección más cercana en el eje Y.
     *
     * Determina la primera celda del mapa en el eje Y que intersecta el rayo.
     *
     * @param angle Ángulo del rayo en radianes.
     * @param position Posición inicial del rayo.
     * @param yNearestLength Distancia desde la posición inicial al punto de impacto en el eje Y.
     * @return Coordenadas del punto de impacto en el eje Y.
     */
    Point2D calculateYNearest(double angle, Point2D position, double& yNearestLength);

    /**
     * @brief Calcula el desplazamiento en el eje X entre celdas.
     *
     * Determina el incremento en las coordenadas para avanzar en el eje X.
     *
     * @param angle Ángulo del rayo en radianes.
     * @param xStepLength Longitud del paso en el eje X.
     * @return Desplazamiento en el eje X.
     */
    Point2D calculateXStep(double angle, double& xStepLength);

    /**
     * @brief Calcula el desplazamiento en el eje Y entre celdas.
     *
     * Determina el incremento en las coordenadas para avanzar en el eje Y.
     *
     * @param angle Ángulo del rayo en radianes.
     * @param yStepLength Longitud del paso en el eje Y.
     * @return Desplazamiento en el eje Y.
     */
    Point2D calculateYStep(double angle, double& yStepLength);

    /**
     * @brief Selecciona el punto de impacto más cercano entre los ejes X e Y.
     *
     * Compara las intersecciones calculadas en ambos ejes y selecciona el más próximo al origen.
     *
     * @param xNearest Resultado del cálculo de raycasting en el eje X.
     * @param yNearest Resultado del cálculo de raycasting en el eje Y.
     * @return El `RayCastResult` correspondiente al impacto más cercano.
     */
    RayCastResult getShortest(RayCastResult xNearest, RayCastResult yNearest);
};


