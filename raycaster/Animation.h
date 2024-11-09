#pragma once
#include <raylib.h>

struct Animation {
	int numFrames;
	int currentFrame;
	double frameTimer;
	double animationSpeed;
	Rectangle textureArea;
	Rectangle positionOnWindow;
	Texture texture;
	bool isAnimationDone();
};
