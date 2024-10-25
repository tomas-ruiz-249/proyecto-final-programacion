#pragma once
#include "Point2D.h"
#include "Map.h"

class Entity {
public:
	Point2D position;
	double angle;
	virtual void move(Map& map) = 0;
	Entity();
private:
protected:
	double rotationSpeed;
	double speed;
};