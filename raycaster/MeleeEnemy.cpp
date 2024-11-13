#include "MeleeEnemy.h"
#include "Player.h"

void MeleeEnemy::attack()
{
	Player* player = Player::getInstance();
	if (sprite->getDistanceFromPlayer(sprite->position, *player) <= 0.5 and player->isAlive() and !player->hurt) {
		player->takeDamage(damage);
	}
}

MeleeEnemy::MeleeEnemy(Point2D position)
{
	this->position = position;
}
