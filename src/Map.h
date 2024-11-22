#pragma once
#include <vector>
#include "Point2D.h"
#include "Enumerations.h"
#define GRID_SIZE 100

class Map {
public:
	bool isPositionEmpty(int row, int column);
	bool isDoor(int row, int column);
	void toggleDoor(int row, int column);
	WallType getElementAt(int row, int column);
	void loadMaps();
	void restoreMaps();
	int getCurrentIndex();
	void setLevel(int level);
	int getMapCount();
	static Map* getInstance();
private:
	std::vector<WallType**> maps;
	WallType** currentMap;
	int currentMapIndex;
	Map();
	static Map* instance;
};