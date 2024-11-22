#pragma once
#include "Item.h"
#include "Pickup.h"

class HealthBox : public Item , public Pickup{
public:
	int healingPoints;
	HealthBox(Point2D pos);
	bool pickup() override;
};
