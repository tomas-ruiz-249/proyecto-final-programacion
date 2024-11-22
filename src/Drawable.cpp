#include <cmath>
#include "Drawable.h"
#include "Player.h"

double Drawable::getDistanceFromPlayer(Point2D position, Player player)
{
    Point2D playerDistance;
	playerDistance.x = position.x - player.position.x;
	playerDistance.y = position.y - player.position.y;
    double dist = (playerDistance.x * playerDistance.x) + (playerDistance.y * playerDistance.y);
	dist = sqrt(dist);
    return dist;
}
