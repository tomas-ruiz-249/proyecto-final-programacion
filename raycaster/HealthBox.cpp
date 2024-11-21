#include "HealthBox.h"

HealthBox::HealthBox(Point2D pos) : Item(pos)
{
	healingPoints = 30;
}

bool HealthBox::pickup()
{
	Player* player = Player::getInstance();
	return player->heal(healingPoints);
}
