#pragma once

#include <vector>
#include <raylib.h>
#include "TextureManager.h"
#include "Point2D.h"
#include "Map.h"
#include "Player.h"
#include "RayCaster.h"
#include "ItemManager.h"
#include "Animated.h"
#include "EnemyManager.h"

/**
 * @class Canvas
 * @brief Clase encargada de la gestión y renderizado de gráficos en el juego.
 *
 * La clase `Canvas` maneja la ventana del juego, el renderizado en 2D y 3D,
 * la animación de sprites y la interfaz de usuario (HUD, menús y transiciones).
 */
class Canvas {
public:
    /**
     * @brief Inicia la ventana del juego.
     *
     * Configura las dimensiones de la ventana y prepara los recursos iniciales.
     */
    void startWindow();

    /**
     * @brief Renderiza los elementos principales del juego.
     *
     * Este método dibuja el mapa, el jugador, los objetos interactivos, los enemigos
     * y los elementos de la interfaz, dependiendo del estado actual del juego.
     *
     * @param map Referencia al mapa actual del juego.
     * @param player Referencia al jugador.
     * @param objManager Referencia al gestor de objetos (ítems).
     * @param enemyManager Referencia al gestor de enemigos.
     * @param state Estado actual del juego.
     * @return El estado siguiente del juego tras completar el ciclo de renderizado.
     */
    GameState draw(const Map& map, Player& player, ItemManager& objManager, EnemyManager& enemyManager, GameState state);

    /**
     * @brief Constructor por defecto.
     *
     * Inicializa la ventana y los valores predeterminados.
     */
    Canvas();

    /**
     * @brief Constructor que configura las dimensiones de la ventana.
     *
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     */
    Canvas(int width, int height);

private:
    TextureManager* textureManager; ///< Administrador de texturas.
    Font titleFont;                 ///< Fuente utilizada para títulos y textos.
    int screenWidth;                ///< Ancho de la pantalla.
    int screenHeight;               ///< Alto de la pantalla.
    int windowWidth;                ///< Ancho de la ventana.
    int windowHeight;               ///< Alto de la ventana.
    int halfWindowWidth;            ///< Mitad del ancho de la ventana.
    int halfWindowHeight;           ///< Mitad del alto de la ventana.
    double backgroundOffset;        ///< Offset para el fondo animado.
    double darkness;                ///< Nivel de oscuridad aplicado en el renderizado.
    std::vector<Drawable*> drawQueue; ///< Cola de objetos a dibujar.

    // Raycasting
    RayCaster rayCaster; ///< Sistema de raycasting para el renderizado 3D.
    double FOV;          ///< Campo de visión en radianes.
    double halfFOV;      ///< Mitad del campo de visión.
    double screenDist;   ///< Distancia virtual desde el jugador a la pantalla.
    double scale;        ///< Escalado de los elementos renderizados.

    /**
     * @brief Renderiza la escena 3D basada en raycasting.
     *
     * @param player Referencia al jugador.
     * @param map Referencia al mapa actual.
     * @param objManager Referencia al gestor de objetos.
     * @param enemyManager Referencia al gestor de enemigos.
     */
    void draw3D(const Player& player, const Map& map, ItemManager& objManager, EnemyManager& enemyManager);

    /**
     * @brief Renderiza una columna específica como parte del renderizado 3D.
     *
     * @param ray Resultado del raycasting para la columna.
     */
    void drawColumn(RayCastResult ray);

    /**
     * @brief Renderiza el arma actual del jugador.
     *
     * @param weapon Referencia al arma del jugador.
     */
    void drawWeapon(Weapon& weapon);

    /**
     * @brief Renderiza el fondo animado del juego.
     *
     * @param player Referencia al jugador para ajustar el fondo según su posición.
     */
    void drawBackground(Player player);

    /**
     * @brief Renderiza el efecto de sangre en la pantalla (daño recibido).
     *
     * @param player Referencia al jugador.
     */
    void drawBlood(Player player);

    /**
     * @brief Gestiona y renderiza la animación de un sprite.
     *
     * @param animated Referencia al objeto animado.
     * @param index Índice de la animación a reproducir.
     * @param color Color aplicado a la animación.
     */
    void animate(Animated& animated, int index, Color color);

    /**
     * @brief Renderiza un sprite animado en relación con la posición del jugador.
     *
     * @param sprite Referencia al sprite animado.
     * @param player Referencia al jugador.
     */
    void drawAnimatedSprite(Animated& sprite, Player player);

    /**
     * @brief Renderiza la interfaz HUD.
     *
     * Muestra información como la salud, munición y otros elementos relevantes.
     *
     * @param player Referencia al jugador.
     */
    void drawHUD(Player& player);

    /**
     * @brief Renderiza un sprite estático en la pantalla.
     *
     * @param sprite Sprite a dibujar.
     * @param player Referencia al jugador.
     */
    void drawStaticSprite(Drawable sprite, Player player);

    /**
     * @brief Renderiza el menú principal.
     * @return El estado siguiente del juego tras mostrar el menú.
     */
    GameState drawMenu();

    /**
     * @brief Renderiza el menú de pausa.
     * @return El estado siguiente del juego tras mostrar el menú de pausa.
     */
    GameState drawPause();

    /**
     * @brief Renderiza el menú de opciones.
     * @return El estado siguiente del juego tras mostrar el menú de opciones.
     */
    GameState drawOptions();

    /**
     * @brief Renderiza una pantalla de transición entre niveles o estados del juego.
     */
    void drawTransitionScreen();
};
