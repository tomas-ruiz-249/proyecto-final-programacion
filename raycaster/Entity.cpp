#include "Entity.h"
#include "raylib.h"
#include <cmath>

Entity::Entity()
{
	position = { 0 , 0 };
	speed = 0.0;
	rotationSpeed = 0.0;
	angle = 0;
}
