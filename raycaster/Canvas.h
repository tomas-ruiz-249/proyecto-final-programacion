#pragma once
#include <raylib.h>
#include "TextureManager.h"
#include "Point2D.h"
#include "Map.h"
#include "Player.h"
#include "RayCaster.h"
//TEST TEST TEST TEST TEST TEST TEST TEST
class Canvas {
public:
	void startWindow();
	void draw(Map map, Player player);
	Canvas();
private:
	TextureManager textureManager;
	int cellSize;
	int screenWidth;
	int halfScreenWidth;
	int screenHeight;
	int halfScreenHeight;

	//raycasting
	RayCaster rayCaster;
	int numRays;
	double FOV;
	double halfFOV;
	double deltaAngle;
	double screenDist;
	double scale;
	double backgroundOffset;
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
};