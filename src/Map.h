#pragma once
#include <vector>
#include "Point2D.h"
#include "Enumerations.h"
#define GRID_SIZE 100

/**
 * @class Map
 * @brief Clase responsable de gestionar los mapas en el juego.
 *
 * La clase `Map` se encarga de cargar, administrar y manipular los mapas del juego.
 * Implementa el patrón Singleton para garantizar una única instancia durante la ejecución.
 * Los mapas están representados como una cuadrícula bidimensional (`GRID_SIZE x GRID_SIZE`).
 */
class Map {
public:
    /**
     * @brief Verifica si una posición específica del mapa está vacía.
     *
     * @param row Fila en la cuadrícula.
     * @param column Columna en la cuadrícula.
     * @return `true` si la posición está vacía o contiene una puerta abierta, `false` en caso contrario.
     */
    bool isPositionEmpty(int row, int column);

    /**
     * @brief Comprueba si una posición contiene una puerta.
     *
     * @param row Fila en la cuadrícula.
     * @param column Columna en la cuadrícula.
     * @return `true` si la posición contiene una puerta cerrada o abierta, `false` en caso contrario.
     */
    bool isDoor(int row, int column);

    /**
     * @brief Alterna el estado de una puerta entre abierta y cerrada.
     *
     * @param row Fila en la cuadrícula.
     * @param column Columna en la cuadrícula.
     *
     * Si la posición contiene una puerta cerrada, se abre. Si está abierta, se cierra.
     * También reproduce un sonido al cambiar el estado.
     */
    void toggleDoor(int row, int column);

    /**
     * @brief Obtiene el elemento presente en una posición específica del mapa.
     *
     * @param row Fila en la cuadrícula.
     * @param column Columna en la cuadrícula.
     * @return El tipo de elemento en la posición (`WallType`).
     *
     * Retorna `none` si la posición está fuera de los límites.
     */
    WallType getElementAt(int row, int column);

    /**
     * @brief Carga los mapas desde archivos de datos.
     *
     * Lee todos los archivos `.txt` en la carpeta de datos y crea una representación de
     * los mapas como matrices bidimensionales (`WallType**`). Los mapas se almacenan en
     * el atributo `maps`.
     */
    void loadMaps();

    /**
     * @brief Restaura los mapas a su estado inicial.
     *
     * Cambia todas las puertas abiertas (`openDoor`) de los mapas al estado cerrado (`closedDoor`).
     */
    void restoreMaps();

    /**
     * @brief Obtiene el índice del mapa actualmente activo.
     *
     * @return Índice del mapa activo (`int`).
     */
    int getCurrentIndex();

    /**
     * @brief Cambia el mapa activo al especificado por índice.
     *
     * @param level Índice del mapa al que se desea cambiar.
     *
     * Si el índice es válido, actualiza `currentMapIndex` y asigna el mapa correspondiente
     * a `currentMap`.
     */
    void setLevel(int level);

    /**
     * @brief Obtiene el número total de mapas cargados.
     *
     * @return Cantidad de mapas (`int`).
     */
    int getMapCount();

    /**
     * @brief Obtiene la instancia única de `Map`.
     *
     * @return Puntero a la instancia única de `Map`.
     *
     * Implementa el patrón Singleton para garantizar que solo haya una instancia de la clase.
     */
    static Map* getInstance();

private:
    std::vector<WallType**> maps; ///< Lista de mapas representados como matrices bidimensionales.
    WallType** currentMap; ///< Puntero al mapa actualmente activo.
    int currentMapIndex; ///< Índice del mapa actualmente activo.
    static Map* instance; ///< Instancia única de la clase (Singleton).

    /**
     * @brief Constructor privado de la clase `Map`.
     *
     * Inicializa el índice del mapa actual y carga los mapas desde los datos.
     */
    Map();
};
