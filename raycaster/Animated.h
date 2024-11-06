#pragma once
#include "Drawable.h"

class Animated : public Drawable {
public:
	int animationIndex;
	std::vector<Animation> animations;
};
