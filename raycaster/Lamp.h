#pragma once
#include "Object.h"

class Lamp : public Object {
public:
	int LampColor;
	Lamp(Point2D pos);
};
