#pragma once
#include <vector>
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"
#include "Object.h"

class Game {
public:
	void startGame();
private:
	void mainLoop();
	Canvas canvas;
	Map map;
	Player player;
	std::vector<Object> objectList;
};