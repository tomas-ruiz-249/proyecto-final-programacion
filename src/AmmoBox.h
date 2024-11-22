#pragma once
#include "Item.h"
#include "Pickup.h"

class AmmoBox : public Item, public Pickup{
public:
	int ammoCount;
	bool pickup() override;
	AmmoBox(Point2D);
};
