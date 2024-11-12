#include <math.h>
#include <raylib.h>
#include "Object.h"

Object::Object()
{
	position = Point2D();
	sprite = nullptr;
}

Object::Object(Point2D position)
{
	this->position = position;
	sprite = nullptr;
}

