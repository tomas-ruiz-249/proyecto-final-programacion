#include "Weapon.h"
#include "TextureManager.h"
#include "Player.h"
#include <iostream>

Weapon::Weapon()
{
	auto texMgr = TextureManager::getInstance();
	sprite = new Animated();
	sprite->tex = texMgr->getTexture("");
	damage = 1000;
	maxAmmo = 10;
	range = 20;
	ammoCount = maxAmmo;
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

bool Weapon::refillAmmo(int refill)
{
	if (ammoCount < maxAmmo) {
		if (ammoCount + refill > maxAmmo) {
			ammoCount = maxAmmo;
		}
		else {
			ammoCount += refill;
		}
		return true;
	}
	return false;
}

int Weapon::getDamage()
{
	return damage;
}

int Weapon::getRange()
{
	return range;
}
