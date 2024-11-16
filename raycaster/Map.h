#pragma once
#include "Point2D.h"
#define GRID_SIZE 100

class Map {
public:
	bool isPositionEmpty(int row, int column);
	int getElementAt(int row, int column);
	void loadMap(const char* fileName);
	static Map* getInstance();
private:
	int grid[GRID_SIZE][GRID_SIZE];
	Map();
	static Map* instance;
};