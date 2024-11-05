#pragma once
#include <raylib.h>
#include <vector>
#include "Animation.h"
#include "Player.h"

class Drawable {
public:
	//part of the texture that will be drawn
	Rectangle textureArea;
	//area of the screen where the texture will be drawn
	Rectangle positionOnWindow;
	//distance from player
	double depth;
	//scale and shift sprite on screen
	double scale;
	double shift;

	Point2D position;

	Texture tex;
	double getDistanceFromPlayer(Point2D position, Player player);
	virtual ~Drawable() = default;
};
