#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

class Object {
public:
	Point2D position;
	Drawable* sprite;

	//constructors
	Object();
	Object(Point2D position);
	virtual ~Object() = default;
private:
};