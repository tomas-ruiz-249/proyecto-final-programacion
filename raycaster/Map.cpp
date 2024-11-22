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
		return currentMap[row][column] == none or currentMap[row][column] == openDoor;
	}
	return false;
}

bool Map::isDoor(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return currentMap[row][column] == closedDoor or currentMap[row][column] == openDoor;
	}
	return false;
}

void Map::toggleDoor(int row, int column)
{
	if (currentMap[row][column] == closedDoor) {
		currentMap[row][column] = openDoor;
	}
	else{
		currentMap[row][column] = closedDoor;
	}
}

WallType Map::getElementAt(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return currentMap[row][column];
	}
	return none;
}

void Map::loadMaps()
{
	FilePathList mapPaths = LoadDirectoryFiles("assets\\data\\");
	for (int i = 0; i < mapPaths.count; i++) {
		auto extension = std::string(GetFileExtension(mapPaths.paths[i]));
		if (extension == ".txt") {
			//create new map
			WallType** newMap = new WallType* [GRID_SIZE];
			for (int i = 0; i < GRID_SIZE; i++) {
				newMap[i] = new WallType[GRID_SIZE];
			}

			if (FileReader::readMapFromFile(mapPaths.paths[i], newMap)) {
				std::cout << "map loaded succesfully from " << mapPaths.paths[i] << std::endl;
			}
			else {
				std::cout << "error loading map " << mapPaths.paths[i] << std::endl;
			}
			maps.push_back(newMap);
		}
	}
}

int Map::getCurrentIndex()
{
	return currentMapIndex;
}

void Map::setLevel(int level)
{
	if (level < maps.size()) {
		currentMapIndex = level;
		currentMap = maps[currentMapIndex];
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
	currentMapIndex = 0;
	loadMaps();
	currentMap = maps[currentMapIndex];
}
