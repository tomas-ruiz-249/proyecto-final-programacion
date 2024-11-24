#include <iostream>
#include <cmath>
#include <algorithm>
#include "Map.h"
#include "Enumerations.h"
#include "FileReader.h"
#include "SoundManager.h"

bool Map::isPositionEmpty(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return currentMap[row][column] == none || currentMap[row][column] == openDoor;
	}
	return false;
}

bool Map::isDoor(int row, int column)
{
	bool isRowValid = row >= 0  && row < GRID_SIZE;
	bool isColumnValid = column >= 0 && column < GRID_SIZE;
	if (isRowValid && isColumnValid) {
		return currentMap[row][column] == closedDoor || currentMap[row][column] == openDoor;
	}
	return false;
}

void Map::toggleDoor(int row, int column)
{
	auto sndMgr = SoundManager::getInstance();
	Sound door = sndMgr->getSound("door_open.mp3");
	PlaySound(door);
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
	FilePathList mapPaths = LoadDirectoryFiles("assets/data/");
	std::vector<std::string> paths;
	for(int i = 0; i < mapPaths.count; i++){
		paths.push_back(mapPaths.paths[i]);
	}
	std::sort(paths.begin(), paths.end(), [](std::string a, std::string b){return a < b;});
	for(auto& path : paths){
		auto extension = std::string(GetFileExtension(path.c_str()));
		if (extension == ".txt") {
			//create new map
			WallType** newMap = new WallType* [GRID_SIZE];
			for (int i = 0; i < GRID_SIZE; i++) {
				newMap[i] = new WallType[GRID_SIZE];
			}

			if (FileReader::readMapFromFile(path.c_str(), newMap)) {
				std::cout << "map loaded succesfully from " << path << std::endl;
			}
			else {
				std::cout << "error loading map " << path << std::endl;
			}
			maps.push_back(newMap);
		}
	}
}

void Map::restoreMaps()
{
	for (auto& map : maps) {
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int j = 0; j < GRID_SIZE; j++) {
				if (isDoor(i, j)) {
					if (map[i][j] == openDoor) {
						map[i][j] = closedDoor;
					}
				}
			}
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

int Map::getMapCount()
{
	return maps.size();
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
