#include "Entity.h"
#include "raylib.h"
#include <cmath>

Entity::Entity()
{
	position = { 5, 24 };
	speed = 5.0;
	rotationSpeed = 0.09f;
	angle = 0;
}
