#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"

class Object {
public:
	ObjectType type;
	double getDistanceFromPlayer(Player& player);
	Object(Point2D pos);
	const Point2D position;
private:
};
