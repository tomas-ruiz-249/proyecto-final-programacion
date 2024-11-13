#include "Entity.h"
#include "raylib.h"
#include <cmath>

bool Entity::isAlive()
{
	return health > 0;
}

int Entity::getHealth()
{
	return health;
}

Entity::Entity()
{
	position = { 0 , 0 };
	speed = 0.0;
	angle = 0;
}

Entity::Entity(unsigned int health)
{
	this->health = health;
	position = { 0 , 0 };
	speed = 0.0;
	angle = 0;
}
