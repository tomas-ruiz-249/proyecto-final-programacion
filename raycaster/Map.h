#pragma once
#define GRID_SIZE 100
#include "Point2D.h"

class Map {
public:
	bool isPositionEmpty(int row, int column);
	int getElementAt(int row, int column);
	Map();
private:
	int grid[GRID_SIZE][GRID_SIZE];
};