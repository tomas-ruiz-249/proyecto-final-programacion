#include "Weapon.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>

Weapon::Weapon()
{
	auto texMgr = TextureManager::getInstance();
	sprite = new Animated();
	sprite->tex = texMgr->getTexture("");
	damage = 20;
	ammoCount = 10;
	reloading = false;
}

void Weapon::shoot()
{
	if (ammoCount) {
		ammoCount--;
		reloading = true;
	}
	else {
		reloading = false;
	}
}

bool Weapon::canShoot()
{
	return not reloading and (ammoCount > 0);
}
