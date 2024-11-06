#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

class Object {
public:
	ObjectType type;
	Point2D position;
	Drawable* sprite;

	//constructors
	Object();
	Object(ObjectType type, Point2D position);
private:
};