#pragma once
#include <vector>
#include "Item.h"
#include "FileReader.h"

/**
 * @class ItemManager
 * @brief Clase responsable de gestionar los ítems del juego.
 *
 * `ItemManager` se encarga de manejar los ítems disponibles en el juego, organizarlos
 * por niveles, verificar si el jugador recoge un ítem, y gestionar la transición entre
 * diferentes listas de ítems. Esta clase sigue el patrón de diseño Singleton.
 */
class ItemManager {
public:
    /**
     * @brief Obtiene la lista actual de ítems en el nivel.
     *
     * @return Un puntero a la lista actual de ítems (`std::vector<Item*>`).
     */
    std::vector<Item*>* getCurrentItemList();

    /**
     * @brief Inicializa las listas de ítems desde los archivos de datos.
     *
     * Lee archivos `.csv` en la carpeta de datos y organiza los ítems por niveles.
     * Los datos se cargan en `itemLists`, y la lista del nivel actual se asigna a `currentItems`.
     */
    void initItems();

    /**
     * @brief Limpia la lista actual de ítems.
     *
     * Borra todos los ítems de `currentItems`, dejando la lista vacía.
     */
    void clearItems();

    /**
     * @brief Verifica si algún ítem está siendo recogido por el jugador.
     *
     * Recorre la lista actual de ítems y comprueba si están lo suficientemente cerca
     * del jugador para ser recogidos. Si el jugador recoge un ítem, este se elimina de
     * la lista y su memoria se libera.
     */
    void checkForPickup();

    /**
     * @brief Obtiene el índice del nivel actual.
     *
     * @return Un entero representando el índice del nivel actual.
     */
    int getCurrentLevel();

    /**
     * @brief Cambia el nivel actual y actualiza la lista de ítems correspondiente.
     *
     * @param level Índice del nivel al que se desea cambiar.
     *
     * Si el índice proporcionado es válido, actualiza `currentLevel` y asigna la
     * lista de ítems correspondiente a `currentItems`.
     */
    void setLevel(int level);

    /**
     * @brief Obtiene la instancia única de `ItemManager`.
     *
     * @return Un puntero a la instancia única de `ItemManager`.
     *
     * Este método implementa el patrón Singleton para garantizar que solo exista
     * una instancia de `ItemManager` en el juego.
     */
    static ItemManager* getInstance();

private:
    int currentLevel; ///< Índice del nivel actual.
    std::vector<std::vector<Item*>> itemLists; ///< Listas de ítems organizadas por niveles.
    std::vector<Item*> currentItems; ///< Lista de ítems activos en el nivel actual.
    static ItemManager* instance; ///< Instancia única de la clase (Singleton).

    /**
     * @brief Constructor privado de `ItemManager`.
     *
     * Inicializa el nivel actual a 0, carga las listas de ítems desde los datos y
     * asigna la lista del nivel inicial a `currentItems`.
     */
    ItemManager();
};
