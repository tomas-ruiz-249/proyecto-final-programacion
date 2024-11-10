#pragma once
#include "Object.h"

class Ammo : public Object {
public:
	int ammoCount;
	Ammo(Point2D);
};
