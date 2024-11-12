#pragma once
#include "Object.h"

class AmmoBox : public Object {
public:
	int ammoCount;
	AmmoBox(Point2D);
};
