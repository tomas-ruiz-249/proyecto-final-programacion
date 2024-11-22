#pragma once
#include <raylib.h>

class Animation {
public:
	int numFrames;
	double frameTimer;
	double animationSpeed;
	Rectangle textureArea;
	Rectangle positionOnWindow;
	Texture texture;
	bool stop;
	int getCurrentFrame();
	bool isAnimationDone();
	void resetAnimation();
	void nextFrame();
private:
	int currentFrame;
};
