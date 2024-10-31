#pragma once
#include <vector>
#include <raylib.h>
#include "TextureManager.h"
#include "Point2D.h"
#include "Map.h"
#include "Player.h"
#include "RayCaster.h"
#include "Object.h"
#include "ObjectManager.h"

class Canvas {
public:
	void startWindow();
	void draw(const Map& map, const Player& player, ObjectManager& objManager);
	Canvas();
	Canvas(int width, int height);
private:
	TextureManager textureManager;
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


	//3d drawing methods
	void draw3D(const Player& player, const Map& map, ObjectManager& objManager);
	void drawColumn(RayCastResult ray);
	void drawWeapon();
	void drawBackground();
	void drawObject(Object& object, const Player& player);
	void drawAnimated(Drawable& sprite, Texture tex);

	//2d drawing methods
	void drawMap(Map map);
	void drawPlayer(Player player);
	void drawRay2D(Point2D position);
	void drawRay2D(Point2D start, Point2D end);
};