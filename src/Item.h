#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

class Item {
public:
	Point2D position;
	Drawable* sprite;

	//constructors
	Item();
	Item(Point2D position);
	virtual ~Item() = default;
private:
};