#pragma once
#include "Animated.h"

class Player;

class Weapon {
public:
	Animated* sprite;
	void shoot();
	bool canShoot();
	bool refillAmmo(int refill);
	int getDamage();
	int getRange();
	Weapon();
	//friend
	friend class Canvas;
	friend class AmmoBox;
 private:
	int damage;
	int range;
	unsigned int ammoCount;
	bool reloading;
	int maxAmmo;
};
