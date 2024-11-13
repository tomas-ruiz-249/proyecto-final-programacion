#include "AmmoBox.h"
#include "Player.h"

bool AmmoBox::pickup()
{
	Player* player = Player::getInstance();
	if (player->weapon->ammoCount < player->weapon->maxAmmo) {
		player->weapon->ammoCount += ammoCount;
		return true;
	}
	return false;
}

AmmoBox::AmmoBox(Point2D pos) : Object(pos)
{
	ammoCount = 10;
}

