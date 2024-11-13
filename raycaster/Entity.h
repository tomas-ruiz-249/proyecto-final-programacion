#pragma once
#include "Point2D.h"
#include "Map.h"

class Entity {
public:
	bool hurt;

	Point2D position;
	double angle;
	double speed;

	int getHealth();
	virtual void act(Map& map) = 0;
	virtual void move(Map map) = 0;
	virtual void takeDamage(int damage) = 0;
	virtual void attack() = 0;
	virtual bool isAlive();
	Entity();
	Entity(unsigned int health);
protected:
	int health;
};