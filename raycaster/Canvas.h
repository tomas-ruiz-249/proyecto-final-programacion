#pragma once
#include <vector>
#include <raylib.h>
#include "TextureManager.h"
#include "Point2D.h"
#include "Map.h"
#include "Player.h"
#include "RayCaster.h"
#include "Object.h"

class Canvas {
public:
	void startWindow();
	void draw(Map& map, Player& player, std::vector<Object>& objects);
	Canvas();
	Canvas(int screenWidth, int screenHeight);
private:
	TextureManager textureManager;
	int cellSize;
	int screenWidth;
	int halfScreenWidth;
	int screenHeight;
	int halfScreenHeight;
	double backgroundOffset;

	//raycasting
	RayCaster rayCaster;
	double FOV;
	double halfFOV;
	double screenDist;
	double scale;

	//2d drawing methods
	void drawMap(Map map);
	void drawPlayer(Player player);
	void drawRay2D(Point2D position);
	void drawRay2D(Point2D start, Point2D end);

	//3d drawing methods
	void draw3D(Player player, Map map);
	void drawColumn(RayCastResult ray);
	void drawWeapon();
	void drawBackground();
	void drawObject(Object& object, Player& player);
};