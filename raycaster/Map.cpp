#include <iostream>
#include <cmath>
#include "Map.h"
#include "Enumerations.h"
#include "FileReader.h"

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

void Map::loadMap(const char* fileName)
{
	if (FileReader::readMapFromFile(fileName, grid)) {
		std::cout << "map loaded succesfully from " << fileName << std::endl;
	}
	else {
		std::cout << "error loading map " << fileName << std::endl;
	}
}

Map* Map::instance;

Map* Map::getInstance()
{
	if (!instance) {
		instance = new Map();
	}
	return instance;
}

Map::Map()
{
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int column = 0; column < GRID_SIZE; column++) {
			grid[row][column] = none;
		}
	}
	loadMap("map.txt");
}
