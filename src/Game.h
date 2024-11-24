#pragma once
#include <vector>
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SoundManager.h"

/**
 * @class Game
 * @brief Gestiona el bucle principal del juego y las transiciones de estado.
 *
 * La clase Game se encarga de la inicialización, renderización y actualizaciones de lógica
 * para el bucle principal del juego. También maneja los estados del juego,
 * transiciones de nivel e interacciones entre los componentes como el jugador,
 * el mapa, los objetos y los enemigos.
 */
class Game {
public:
    /**
     * @brief Inicia el juego entrando en el bucle principal.
     *
     * Inicializa la ventana del juego y comienza a manejar la renderización
     * y las actualizaciones de lógica.
     */
    void startGame();

    /**
     * @brief Obtiene el estado actual del juego.
     * @return El valor actual del enum GameState.
     */
    GameState getState();

    /**
     * @brief Construye el objeto Game e inicializa los sistemas principales.
     *
     * Inicializa la ventana del juego, el dispositivo de audio, el gestor de sonidos
     * y los componentes del juego como el mapa y el jugador.
     */
    Game();

private:
    /**
     * @brief Inicializa el juego para el nivel actual.
     *
     * Restablece al jugador, restaura los mapas, inicializa los objetos y enemigos,
     * y configura el nivel actual.
     */
    void initGame();

    /**
     * @brief El bucle principal del juego que maneja la renderización y las actualizaciones de lógica.
     *
     * Actualiza continuamente el juego hasta que se cierre la ventana.
     */
    void mainLoop();

    /**
     * @brief Maneja todas las operaciones de renderización.
     *
     * Dibuja el mapa actual, el jugador, los objetos y los enemigos en el lienzo según el estado del juego.
     */
    void render();

    /**
     * @brief Actualiza la lógica del juego y las transiciones entre estados.
     *
     * Maneja las acciones del jugador, el comportamiento de los enemigos, la recolección de objetos
     * y las transiciones de estado, como pausar o finalizar el juego.
     */
    void logic();

    /**
     * @brief Reproduce la música de fondo para el nivel actual.
     *
     * Asegura que se reproduzca la banda sonora apropiada según el índice del mapa actual.
     */
    void playCurrentSong();

    /**
     * @brief Avanza el juego al siguiente nivel.
     *
     * Actualiza el índice del nivel actual, restablece al jugador, inicializa los objetos y enemigos
     * para el nuevo nivel y carga el mapa correspondiente.
     */
    void nextLevel();

    int currentLevel;                 ///< El índice del nivel actual.
    Sound currentSong;                ///< La música de fondo actual que se está reproduciendo.
    Canvas canvas;                    ///< El lienzo de renderización para el juego.
    Map* map;                         ///< Puntero a la instancia de Map que gestiona los niveles del juego.
    Player* player;                   ///< Puntero a la instancia de Player.
    SoundManager* soundMgr;           ///< Puntero al singleton SoundManager.
    ItemManager* itemManager;         ///< Puntero al singleton ItemManager.
    EnemyManager enemyManager;        ///< Gestiona todas las entidades enemigas en el juego.
    GameState currentState;           ///< El estado actual del juego.
    GameState newState;               ///< El próximo estado al que se transicionará según la lógica del juego.
};
