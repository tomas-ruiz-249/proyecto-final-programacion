#pragma once
#include <raylib.h>

class Drawable {
public:
	//part of the texture that will be drawn
	Rectangle textureArea;
	//area of the screen where the texture will be drawn
	Rectangle positionOnWindow;
	//distance from player
	double depth;
	bool animated;

	//scale and shift sprite;
	double scale;
	double shift;
	virtual ~Drawable() = default;
};
