#pragma once
#include "Object.h"

class Health : public Object {
public:
	int healingPoints;
	Health(Point2D pos);
};
