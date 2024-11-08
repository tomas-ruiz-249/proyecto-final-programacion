#pragma once
#include <vector>
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"
#include "Enemy.h"
#include "EnemyManager.h"

class Game {
public:
	void startGame();
	Game();
private:
	void mainLoop();
	Canvas canvas;
	Map map;
	Player player;
	ObjectManager objManager;
	EnemyManager enemyManager;
};