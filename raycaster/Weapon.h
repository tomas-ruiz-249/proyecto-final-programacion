#pragma once
#include "Animated.h"

class Player;

class Weapon {
public:
	Animated* sprite;
	int damage;
	unsigned int ammoCount;
	void shoot();
	bool canShoot();
	Weapon();
	//friend
	friend class Canvas;
private:
	bool reloading;
};
