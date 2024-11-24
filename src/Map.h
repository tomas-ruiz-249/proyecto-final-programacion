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
 * Implementa el patr�n Singleton para garantizar una �nica instancia durante la ejecuci�n.
 * Los mapas est�n representados como una cuadr�cula bidimensional (`GRID_SIZE x GRID_SIZE`).
 */

class Map {
public:
    /**
     * @brief Verifica si una posici�n espec�fica del mapa est� vac�a.
     *
     * @param row Fila en la cuadr�cula.
     * @param column Columna en la cuadr�cula.
     * @return `true` si la posici�n est� vac�a o contiene una puerta abierta, `false` en caso contrario.
     */
    bool isPositionEmpty(int row, int column);

    /**
     * @brief Comprueba si una posici�n contiene una puerta.
     *
     * @param row Fila en la cuadr�cula.
     * @param column Columna en la cuadr�cula.
     * @return `true` si la posici�n contiene una puerta cerrada o abierta, `false` en caso contrario.
     */
    bool isDoor(int row, int column);

    /**
     * @brief Alterna el estado de una puerta entre abierta y cerrada.
     *
     * @param row Fila en la cuadr�cula.
     * @param column Columna en la cuadr�cula.
     *
     * Si la posici�n contiene una puerta cerrada, se abre. Si est� abierta, se cierra.
     * Tambi�n reproduce un sonido al cambiar el estado.
     */
    void toggleDoor(int row, int column);

    /**
     * @brief Obtiene el elemento presente en una posici�n espec�fica del mapa.
     *
     * @param row Fila en la cuadr�cula.
     * @param column Columna en la cuadr�cula.
     * @return El tipo de elemento en la posici�n (`WallType`).
     *
     * Retorna `none` si la posici�n est� fuera de los l�mites.
     */
    WallType getElementAt(int row, int column);

    /**
     * @brief Carga los mapas desde archivos de datos.
     *
     * Lee todos los archivos `.txt` en la carpeta de datos y crea una representaci�n de
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
     * @brief Obtiene el �ndice del mapa actualmente activo.
     *
     * @return �ndice del mapa activo (`int`).
     */
    int getCurrentIndex();

    /**
     * @brief Cambia el mapa activo al especificado por �ndice.
     *
     * @param level �ndice del mapa al que se desea cambiar.
     *
     * Si el �ndice es v�lido, actualiza `currentMapIndex` y asigna el mapa correspondiente
     * a `currentMap`.
     */
    void setLevel(int level);

    /**
     * @brief Obtiene el n�mero total de mapas cargados.
     *
     * @return Cantidad de mapas (`int`).
     */
    int getMapCount();

    /**
     * @brief Obtiene la instancia �nica de `Map`.
     *
     * @return Puntero a la instancia �nica de `Map`.
     *
     * Implementa el patr�n Singleton para garantizar que solo haya una instancia de la clase.
     */
    static Map* getInstance();

private:
    std::vector<WallType**> maps; ///< Lista de mapas representados como matrices bidimensionales.
    WallType** currentMap; ///< Puntero al mapa actualmente activo.
    int currentMapIndex; ///< �ndice del mapa actualmente activo.
    static Map* instance; ///< Instancia �nica de la clase (Singleton).
    void normalizePathSeparator(char* path);

    /**
     * @brief Constructor privado de la clase `Map`.
     *
     * Inicializa el �ndice del mapa actual y carga los mapas desde los datos.
     */
    Map();
};
