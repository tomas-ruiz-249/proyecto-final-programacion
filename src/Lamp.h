#pragma once
#include "Item.h"

class Lamp : public Item {
public:
	int LampColor;
	Lamp(Point2D pos);
};
