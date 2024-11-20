#include "Game.h"
#include <iostream>

void Game::startGame()
{
	mainLoop();
}

GameState Game::getState()
{
	return currentState;
}

Game::Game()
{
	InitWindow(0, 0, "");
	int width = GetScreenWidth();
	int height = GetScreenHeight();
	CloseWindow();
	canvas = Canvas(width, height);
	canvas.startWindow();
	InitAudioDevice();
	soundMgr = SoundManager::getInstance();
	soundMgr->loadSounds();

	map = Map::getInstance();
	player = Player::getInstance();
	currentState = mainMenu;
}

void Game::initGame()
{
	objManager.initObjects();
	enemyManager.initEnemies();
	player->reset();
}

void Game::mainLoop()
{
	std::string fps;
	while (!WindowShouldClose()) {
		fps = std::to_string(GetFPS());
		SetWindowTitle(fps.c_str());
		render();
		logic();
	}
}

void Game::render()
{
	newState = canvas.draw(*map, *player, objManager, enemyManager, currentState);
}

void Game::logic()
{
	if (newState != na) 
	{
		currentState = newState;
	}
	

	switch (currentState) {
		case mainMenu:
			initGame();
			break;
		case playing:
			//correr juego normalmente
			player->act(*map);
			objManager.checkForPickup();
			enemyManager.runEnemyBehaviour(*player, *map);

			//pausar juego si se presiona p y causar game over si jugador muere
			if (IsKeyPressed(KEY_P) and player->isAlive()) 
			{
				currentState = pause;
			}
			if (!player->isAlive()) 
			{
				currentState = gameOver;
			}
			break;
		case pause:
			//renaudar juego al presionar p
			if (IsKeyPressed(KEY_P)) 
			{
				currentState = playing;
			}
			break;
		case gameOver:
			if (IsKeyPressed(KEY_ENTER)) 
			{
				currentState = mainMenu;
			}
			break;
		case options:
			if (IsKeyPressed(KEY_P)) 
			{
				currentState = pause;
			}
			break;
		case end:
			CloseWindow();
			break;
	}
}
