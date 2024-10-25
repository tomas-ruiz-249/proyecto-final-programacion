#pragma once
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"

class Game {
public:
	void startGame();
private:
	void mainLoop();
	Canvas canvas;
	Map map;
	Player player;
};