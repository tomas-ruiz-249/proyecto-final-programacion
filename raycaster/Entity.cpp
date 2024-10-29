#include "Entity.h"
#include "raylib.h"
#include <cmath>

Entity::Entity()
{
	position = { 2.1, 8 };
	speed = 5.0;
	rotationSpeed = 0.09f;
	angle = PI * 2 / 6;
}
