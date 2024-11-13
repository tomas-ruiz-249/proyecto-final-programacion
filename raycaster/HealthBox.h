#pragma once
#include "Object.h"
#include "Pickup.h"

class HealthBox : public Object , public Pickup{
public:
	int healingPoints;
	HealthBox(Point2D pos);
	bool pickup() override;
};
