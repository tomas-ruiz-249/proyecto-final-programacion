#pragma once
#include "Point2D.h"
#include "Map.h"

class Entity {
public:
	bool hurt;
	unsigned int health;

	Point2D position;
	double angle;

	virtual void act(Map& map) = 0;
	virtual void takeDamage(int damage) = 0;
	virtual bool isAlive();
	Entity();
private:
protected:
	double rotationSpeed;
	double speed;
};