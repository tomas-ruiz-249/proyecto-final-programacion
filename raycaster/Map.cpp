#include "Map.h"
#include <cmath>

bool Map::isPositionEmpty(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return grid[row][column] == 0;
	}
	return false;
}

int Map::getElementAt(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return grid[row][column];

	}
	return  0;
}

Map::Map()
{
	int arr[GRID_SIZE][GRID_SIZE] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,2,2,2,1},
	};

	for (int row = 0; row < GRID_SIZE; row++) {
		for (int column = 0; column < GRID_SIZE; column++) {
			grid[row][column] = arr[row][column];
		}
	}
}
