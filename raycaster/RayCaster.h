#pragma once
#include "Map.h"
#include "Enumerations.h"

typedef struct RayCastResult{
	Point2D hitCoordinates;
	double length;
	int index;
	double textureOffset;
	WallType wall;
	double cos;
	double sin;
}RayCastResult;

class RayCaster {
public:
	RayCastResult rayCast(double angle, Point2D position, Map& map);
private:
	Point2D calculateXNearest(double angle, Point2D position, double& xNearestLength);
	Point2D calculateYNearest(double angle, Point2D position, double& yNearestLength);
	Point2D calculateXStep(double angle, double& xStepLength);
	Point2D calculateYStep(double angle, double& yStepLength);
	RayCastResult getShortest(RayCastResult xNearest, RayCastResult yNearest);
};

