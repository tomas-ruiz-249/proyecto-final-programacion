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
 * clase que maneja graficos
*/

class Canvas {
public:
	void startWindow();
	GameState draw(const Map& map, Player & player, ItemManager& objManager, EnemyManager& enemyManager, GameState state); /**< method that draws to window */
	Canvas();/**< main constructor */
	Canvas(int width, int height);
private:
	TextureManager* textureManager;
	Font titleFont;
	int screenWidth;
	int screenHeight;
	int windowWidth;
	int windowHeight;
	int halfWindowWidth;
	int halfWindowHeight;
	double backgroundOffset;
	double darkness;
	std::vector<Drawable*> drawQueue;

	//raycasting
	RayCaster rayCaster;
	double FOV;
	double halfFOV;
	double screenDist;
	double scale;

	void draw3D(const Player& player, const Map& map, ItemManager& objManager, EnemyManager& enemyManager);
	void drawColumn(RayCastResult ray);
	void drawWeapon(Weapon& weapon);
	void drawBackground(Player player);
	void drawBlood(Player player);
	void animate(Animated& animated, int index, Color color);
	void drawAnimatedSprite(Animated& sprite, Player player);
	void drawHUD(Player& player);
	void drawStaticSprite(Drawable sprite, Player player);
	GameState drawMenu();
	GameState drawPause();
	GameState drawOptions();
	void drawTransitionScreen();
};