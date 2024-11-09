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
	player = Player();
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
	canvas.draw(map, player, objManager, enemyManager);
	for (auto& enemy : *enemyManager.getEnemyList()) {
		if (enemy.hurt and enemy.sprite->animations.size() > 1) {
			enemy.sprite->animationIndex = 1;
			auto& anim = enemy.sprite->animations[enemy.sprite->animationIndex];
			if (anim.isAnimationDone()) {
				enemy.hurt = false;
			}
		}
		else {
			enemy.sprite->animationIndex = 0;
		}
	}
}

void Game::logic()
{
	player.act(map);
	for (auto& enemy : *enemyManager.getEnemyList()) {
		if (player.justShot and enemy.sprite->isOnScreenCenter) {
			enemy.hurt = true;
		}
	}
	player.justShot = false;
}
