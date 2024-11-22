#include "AmmoBox.h"
#include "Player.h"

bool AmmoBox::pickup()
{
	Player* player = Player::getInstance();
	return player->weapon->refillAmmo(ammoCount);
}

AmmoBox::AmmoBox(Point2D pos) : Item(pos)
{
	ammoCount = 15;
}

