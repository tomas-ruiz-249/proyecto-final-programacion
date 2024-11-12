#include "Game.h"
#include <iostream>

void Game::startGame()
{
	InitWindow(0, 0, "");
	int width = GetScreenWidth();
	int height = GetScreenHeight();
	CloseWindow();
	canvas = Canvas(width, height);
	canvas.startWindow();
	player = Player::getInstance();
	objManager.initObjects();
	enemyManager.initEnemies();
	mainLoop();
}

Game::Game()
{
	map = Map();
	canvas = Canvas();
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
	canvas.draw(map, *player, objManager, enemyManager);
}

void Game::logic()
{
	player->act(map);
	enemyManager.runEnemyBehaviour(*player, map);
}
