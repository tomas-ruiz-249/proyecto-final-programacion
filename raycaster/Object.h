#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

class Object : public Drawable{
public:
	ObjectType type;
	Point2D position;
	double getDistanceFromPlayer(const Player& player);

	//constructors
	Object();
	Object(ObjectType type, Point2D position, double scale, double shift);
private:
};
