#include "HealthBox.h"

HealthBox::HealthBox(Point2D pos) : Object(pos)
{
	healingPoints = 10;
}

bool HealthBox::pickup()
{
	Player* player = Player::getInstance();
	return player->heal(healingPoints);
}
