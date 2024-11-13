#pragma once
#include "Object.h"
#include "Pickup.h"

class AmmoBox : public Object, public Pickup{
public:
	int ammoCount;
	bool pickup() override;
	AmmoBox(Point2D);
};
