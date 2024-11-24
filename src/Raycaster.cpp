#include <cmath>
#include <raylib.h>
#include <iostream>
#include "RayCaster.h"

RayCastResult RayCaster::rayCast(double angle, Point2D position, Map& map)
{
	IPoint2D gridPos = { 0,0 };
	int maxDepth = GRID_SIZE;

	RayCastResult xNearest;
	xNearest.cos = cos(angle);
	xNearest.sin = sin(angle);
	xNearest.depth = 0.0;
	xNearest.hitCoordinates = calculateXNearest(angle, position, xNearest.depth);
	double xStepLength = 0.0;
	Point2D xStep = calculateXStep(angle, xStepLength);
	gridPos.x = static_cast<unsigned int>(xNearest.hitCoordinates.x);

	while (gridPos.x < maxDepth) {
		gridPos.x = static_cast<unsigned int>(xNearest.hitCoordinates.x);
		gridPos.y = static_cast<unsigned int>(xNearest.hitCoordinates.y);
		if (!map.isPositionEmpty(gridPos.y, gridPos.x) || gridPos.x >= maxDepth) {
			xNearest.wall = map.getElementAt(gridPos.y, gridPos.x);
			break;
		}
		xNearest.hitCoordinates.x += xStep.x;
		xNearest.hitCoordinates.y += xStep.y;
		xNearest.depth += xStepLength;
	}

	RayCastResult yNearest;
	yNearest.cos = cos(angle);
	yNearest.sin = sin(angle);
	yNearest.depth = 0.0;
	yNearest.hitCoordinates = calculateYNearest(angle, position, yNearest.depth);
	double yStepLength = 0.0;
	Point2D yStep = calculateYStep(angle, yStepLength);
	gridPos.y = static_cast<unsigned int>(yNearest.hitCoordinates.y);

	while (gridPos.y < maxDepth) {
		gridPos.x = static_cast<unsigned int>(yNearest.hitCoordinates.x);
		gridPos.y = static_cast<unsigned int>(yNearest.hitCoordinates.y);
		if (!map.isPositionEmpty(gridPos.y, gridPos.x) || gridPos.y >= maxDepth) {
			yNearest.wall = map.getElementAt(gridPos.y, gridPos.x);
			break;
		}
		yNearest.hitCoordinates.x += yStep.x;
		yNearest.hitCoordinates.y += yStep.y;
		yNearest.depth += yStepLength;
	}
	return getShortest(xNearest, yNearest);
}

std::vector<RayCastResult> RayCaster::getAllRays(double rayAngle, Player player, Map map)
{
	RayCastResult hit;
	for (int ray = 0; ray < numRays; ray++) {
		hit = rayCast(rayAngle, player.position, map);
		hit.depth *= cos(player.angle - rayAngle);
		hit.index = ray;
		rays.push_back(hit);
		rayAngle += deltaAngle;
	}
	return rays;
}

double RayCaster::getDeltaAngle()
{
	return deltaAngle;
}

double RayCaster::getNumRays()
{
	return numRays;
}

void RayCaster::clearRays()
{
	rays.clear();
}

RayCaster::RayCaster(int numRays, double deltaAngle)
{
	this->numRays = numRays;
	this->deltaAngle = deltaAngle;
}

RayCaster::RayCaster()
{
}

Point2D RayCaster::calculateXNearest(double angle, Point2D position, double& xNearestLength)
{
	double cosA = cos(angle);
	double sinA = sin(angle);
	Point2D xNearest ;
	int mapX = (int)position.x;
	if (cosA > 0) {
		xNearest.x = mapX + 1;
	}
	else {
		xNearest.x = mapX - 1e-6;
	}
	xNearestLength = (xNearest.x - position.x) / cosA;
	xNearest.y = position.y + xNearestLength * sinA;
	return xNearest;
}

Point2D RayCaster::calculateYNearest(double angle, Point2D position, double& yNearestLength)
{
	double cosA = cos(angle);
	double sinA = sin(angle);
	Point2D yNearest;
	int mapY = (int)position.y;
	if (sinA > 0) {
		yNearest.y = mapY + 1;
	}
	else {
		yNearest.y = mapY - 1e-6;
	}
	yNearestLength = (yNearest.y - position.y) / sinA;
	yNearest.x = position.x + yNearestLength * cosA;
	return yNearest;
}

Point2D RayCaster::calculateXStep(double angle, double& xStepLength)
{
	Point2D xStep;
	double cosA = cos(angle);
	double sinA = sin(angle);
	if (cosA > 0) {
		xStep.x = 1;
	}
	else {
		xStep.x = -1;
	}
	xStepLength = xStep.x / cosA;
	xStep.y = xStepLength * sinA;
	return xStep;
}

Point2D RayCaster::calculateYStep(double angle, double& yStepLength)
{
	Point2D yStep;
	double cosA = cos(angle);
	double sinA = sin(angle);
	if (sinA > 0) {
		yStep.y = 1;
	}
	else {
		yStep.y = -1;
	}
	yStepLength = yStep.y / sinA;
	yStep.x = yStepLength * cosA;
	return yStep;
}

RayCastResult RayCaster::getShortest(RayCastResult xNearest, RayCastResult yNearest)
{
	if (std::abs(xNearest.depth) < std::abs(yNearest.depth)) {
		xNearest.hitCoordinates.y = fmod(xNearest.hitCoordinates.y, 1);
		if (xNearest.cos > 0) {
			xNearest.horizontalTextureOffset = xNearest.hitCoordinates.y;
		}
		else {
			xNearest.horizontalTextureOffset = 1 - xNearest.hitCoordinates.y;
		}
		return xNearest;
	}
	else {
		yNearest.hitCoordinates.x = fmod(yNearest.hitCoordinates.x, 1);
		if (yNearest.cos > 0) {
			yNearest.horizontalTextureOffset = 1 - yNearest.hitCoordinates.x;
		}
		else {
			yNearest.horizontalTextureOffset = yNearest.hitCoordinates.x;
		}
		return yNearest;
	}
}

