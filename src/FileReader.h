#pragma once
#include <vector>
#include "Map.h"
#include "Item.h"
#include "Enemy.h"

/**
 * @class FileReader.h
 * @brief Declaración de la clase FileReader para manejar la lectura de datos de archivos en el juego.
 *
 * La clase FileReader proporciona funciones estáticas para cargar datos de archivos externos,
 * incluyendo el mapa, los ítems y los enemigos que se utilizarán en el juego.
 */

 /**
  * @class FileReader
  * @brief Clase para leer y cargar datos desde archivos.
  *
  * Esta clase contiene métodos estáticos que permiten leer el mapa, ítems y enemigos desde
  * archivos externos y cargarlos en estructuras adecuadas para su uso en el juego.
  */
class FileReader {
public:
    /**
     * @brief Lee los datos del mapa desde un archivo y los carga en una matriz 2D.
     *
     * @param fileName Nombre del archivo que contiene los datos del mapa.
     * @param map Matriz bidimensional donde se almacenará el mapa.
     * @return `true` si el archivo se leyó correctamente, `false` si ocurrió un error.
     *
     * El archivo debe contener valores separados por comas, donde cada valor representa
     * un tipo de pared definido por la enumeración `WallType`.
     */
    static bool readMapFromFile(const char* fileName, WallType** map);

    /**
     * @brief Lee los datos de los ítems desde un archivo y los carga en una lista.
     *
     * @param fileName Nombre del archivo que contiene los datos de los ítems.
     * @param itemList Vector donde se almacenarán los ítems instanciados.
     * @return `true` si el archivo se leyó correctamente, `false` si ocurrió un error.
     *
     * El archivo debe contener líneas con los datos de cada ítem en el formato:
     * `ItemType,posiciónX,posiciónY`. Se instanciará un ítem basado en su tipo
     * y se añadirá a la lista proporcionada.
     */
    static bool readItemsFromFile(const char* fileName, std::vector<Item*>& itemList);

    /**
     * @brief Lee los datos de los enemigos desde un archivo y los carga en una lista.
     *
     * @param fileName Nombre del archivo que contiene los datos de los enemigos.
     * @param enemyList Vector donde se almacenarán los enemigos instanciados.
     * @return `true` si el archivo se leyó correctamente, `false` si ocurrió un error.
     *
     * El archivo debe contener líneas con los datos de cada enemigo en el formato:
     * `EnemyType,posiciónX,posiciónY`. Se instanciará un enemigo basado en su tipo
     * y se añadirá a la lista proporcionada.
     */
    static bool readEnemiesFromFile(const char* fileName, std::vector<Enemy*>& enemyList);
};
