#include "Enemy.h"
#include <iostream>

void Enemy::act(Map& map)
{
}

void Enemy::takeDamage(int damage)
{
	if (isAlive()) {
		hurt = true;
		health -= damage;
	}
}
