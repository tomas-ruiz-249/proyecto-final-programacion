#pragma once
#include "Point2D.h"
#include "Animated.h"

class Projectile {
public:
	Animated* sprite;
	bool shoot();
	Point2D getPosition();
	Projectile(Point2D pos, double ang, int damage);
private:
	int damage;
	double timeLimit;
	double timer;
	double speed;
	double angle;
	Point2D position;
};
