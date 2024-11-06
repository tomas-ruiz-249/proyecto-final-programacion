#include <math.h>
#include <raylib.h>
#include "Object.h"

Object::Object()
{
	position = Point2D();
	type = invalid;
	sprite = nullptr;
}

Object::Object(ObjectType type, Point2D position)
{
	this->type = type;
	this->position = position;
	sprite = nullptr;
}

