#pragma once
#include <raylib.h>

struct Drawable {
	//part of the texture that will be drawn
	Rectangle textureArea;
	//area of the screen where the texture will be drawn
	Rectangle positionOnWindow;
	double depth;
	virtual ~Drawable() = default;
};
