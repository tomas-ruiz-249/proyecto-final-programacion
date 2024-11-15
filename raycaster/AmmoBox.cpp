#include "AmmoBox.h"
#include "Player.h"

bool AmmoBox::pickup()
{
	Player* player = Player::getInstance();
	return player->weapon->refillAmmo(ammoCount);
}

AmmoBox::AmmoBox(Point2D pos) : Object(pos)
{
	ammoCount = 10;
}

