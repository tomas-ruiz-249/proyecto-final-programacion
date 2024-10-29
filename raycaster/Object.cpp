#include <math.h>
#include <raylib.h>
#include "Object.h"
//cambios cambios cambios

double Object::getDistanceFromPlayer(const Player & player)
{
	Point2D playerDistance;
	playerDistance.x = position.x - player.position.x;
	playerDistance.y = position.y - player.position.y;
	double dist = (playerDistance.x * playerDistance.x) + (playerDistance.y * playerDistance.y);
	dist = sqrt(dist);
    return dist;
}

Object::Object(Point2D pos) : position(pos)
{
	type = health;
}

Object::Object()
{
	position = Point2D();
	type = health;
}
