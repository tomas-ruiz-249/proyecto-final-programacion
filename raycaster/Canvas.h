#pragma once
#include <vector>
#include <raylib.h>
#include "TextureManager.h"
#include "Point2D.h"
#include "Map.h"
#include "Player.h"
#include "RayCaster.h"
#include "ObjectManager.h"
#include "Animated.h"
#include "EnemyManager.h"

class Canvas {
public:
	void startWindow();
	GameState draw(const Map& map, Player & player, ObjectManager& objManager, EnemyManager& enemyManager, GameState state);
	Canvas();
	Canvas(int width, int height);
private:
	TextureManager* textureManager;
	Font doomFont;
	int screenWidth;
	int screenHeight;
	int windowWidth;
	int windowHeight;
	int halfWindowWidth;
	int halfWindowHeight;
	double backgroundOffset;
	int cellSize;
	double darkness;
	std::vector<Drawable*> drawQueue;

	//raycasting
	RayCaster rayCaster;
	double FOV;
	double halfFOV;
	double screenDist;
	double scale;

	//first person drawing methods

	void draw3D(const Player& player, const Map& map, ObjectManager& objManager, EnemyManager& enemyManager);
	void drawColumn(RayCastResult ray);
	void drawWeapon(Weapon& weapon);
	void drawBackground(Player player);
	void drawBlood(Player player);
	void animate(Animated& animated, int index, Color color);
	void drawAnimatedSprite(Animated& sprite, Player player);
	void drawHUD(Player& player);
	void drawStaticSprite(Drawable sprite, Player player);

	//2d drawing methods
	void drawMap(Map map);
	void drawPlayer(Player player);
	void drawRay2D(Point2D position);
	void drawRay2D(Point2D start, Point2D end);
	GameState drawMenu();
	GameState drawPause();
	GameState drawOptions();
};