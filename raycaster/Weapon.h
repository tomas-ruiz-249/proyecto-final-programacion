#pragma once
#include "Animated.h"

class Player;

class Weapon {
public:
	Animated* sprite;
	int damage;
	bool reloading;
	Weapon();
private:
};
