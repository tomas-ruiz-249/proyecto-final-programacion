#pragma once
#include <raylib.h>

struct Animation {
	int numFrames;
	int currentFrame;
	double frameTimer;
	double animationSpeed;
	Texture texture;
};
