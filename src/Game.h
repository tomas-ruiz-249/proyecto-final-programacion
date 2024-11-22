#pragma once
#include <vector>
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SoundManager.h"

class Game {
public:
	void startGame();
	GameState getState();
	Game();
private:
	void initGame();
	void mainLoop();
	void render();
	void logic();
	void playCurrentSong();
	void nextLevel();
	int currentLevel;
	Sound currentSong;
	Canvas canvas;
	Map* map;
	Player* player;
	SoundManager* soundMgr;
	ItemManager* itemManager;
	EnemyManager enemyManager;
	GameState currentState;
	GameState newState;
};