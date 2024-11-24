#pragma once

#include <vector>
#include "Enemy.h"

/**
 * @class EnemyManager
 * @brief Administra la lógica y el comportamiento de los enemigos en el juego.
 *
 * La clase `EnemyManager` se encarga de manejar una lista de enemigos,
 * inicializarlos, gestionar su comportamiento, aplicar daño y verificar su estado.
 */
class EnemyManager {
public:
    /**
     * @brief Obtiene la lista de enemigos actuales.
     *
     * @return Un puntero a un vector de enemigos (`Enemy*`).
     */
    std::vector<Enemy*>* getEnemyList();

    /**
     * @brief Inicializa los enemigos en el nivel actual.
     *
     * Este método crea nuevos enemigos basándose en objetos del nivel,
     * asignándoles sprites y animaciones específicas según su tipo.
     */
    void initEnemies();

    /**
     * @brief Limpia la lista de enemigos.
     *
     * Libera la memoria asignada para los enemigos actuales y vacía la lista.
     */
    void clearEnemies();

    /**
     * @brief Ejecuta el comportamiento de todos los enemigos.
     *
     * Este método actualiza el estado de cada enemigo en la lista, aplica daño
     * cuando sea necesario y actualiza sus animaciones.
     *
     * @param player Referencia al jugador.
     * @param map Mapa del nivel actual.
     */
    void runEnemyBehaviour(Player& player, Map map);

    /**
     * @brief Verifica si todos los enemigos están muertos.
     *
     * @return `true` si todos los enemigos están muertos, `false` en caso contrario.
     */
    bool areEnemiesDead();

private:
    /**
     * @brief Aplica daño a un enemigo, si corresponde.
     *
     * Este método determina si un enemigo puede recibir daño basado en
     * la posición, distancia y el estado del jugador (si disparó recientemente).
     *
     * @param enemy Puntero al enemigo que podría recibir daño.
     * @param player Referencia al jugador.
     * @param map Mapa del nivel actual.
     */
    void damageEnemy(Enemy* enemy, Player player, Map map);

    /**
     * @brief Actualiza el estado visual del enemigo.
     *
     * Cambia la animación del enemigo según su estado actual:
     * - Animación de herido si está herido.
     * - Animación de muerte si está muerto.
     * - Animación de caminar si está vivo y saludable.
     *
     * @param enemy Puntero al enemigo cuyo estado se actualizará.
     */
    void setEnemyState(Enemy* enemy);

    /**
     * @brief Lista de enemigos actuales en el nivel.
     */
    std::vector<Enemy*> enemyList;
};
