#include <math.h>
#include <raylib.h>
#include "Item.h"

Item::Item()
{
	position = Point2D();
	sprite = nullptr;
}

Item::Item(Point2D position)
{
	this->position = position;
	sprite = nullptr;
}

