#pragma once
#include "Point2D.h"
#include "Map.h"

class Entity {
public:
	Point2D position;
	bool hurt;
	double angle;
	virtual void act(Map& map) = 0;
	virtual void takeDamage() = 0;
	Entity();
private:
protected:
	double rotationSpeed;
	double speed;
};