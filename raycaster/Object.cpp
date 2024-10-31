#include <math.h>
#include <raylib.h>
#include "Object.h"

double Object::getDistanceFromPlayer(const Player & player)
{
    Point2D playerDistance;
	playerDistance.x = position.x - player.position.x;
	playerDistance.y = position.y - player.position.y;
    double dist = (playerDistance.x * playerDistance.x) + (playerDistance.y * playerDistance.y);
	dist = sqrt(dist);
    return dist;
}

Object::Object()
{
	position = Point2D();
	type = invalid;
	scale = 1;
	shift = 0;
}

Object::Object(ObjectType type, Point2D position, double scale, double shift)
{
	this->type = type;
	this->position = position;
	this->scale = scale;
	this->shift = shift;
}
