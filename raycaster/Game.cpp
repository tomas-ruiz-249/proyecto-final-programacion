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
	for (auto& enemy : *enemyManager.getEnemyList()) {
		if (enemy.isAlive() and enemy.hurt) {
			enemy.sprite->animationIndex = 1;
			auto& anim = enemy.sprite->animations[enemy.sprite->animationIndex];
			if (anim.isAnimationDone()) {
				anim.resetAnimation();
				enemy.hurt = false;
			}
		}
		else {
			if (!enemy.isAlive()) {
				enemy.sprite->animationIndex = 2;
				auto& deathAnimation = enemy.sprite->animations[enemy.sprite->animationIndex];
				if (deathAnimation.isAnimationDone()) {
					deathAnimation.stop = true;
				}
			}
			else {
				enemy.sprite->animationIndex = 0;
			}
		}
	}
	canvas.draw(map, player, objManager, enemyManager);
}

void Game::logic()
{
	player.act(map);
	RayCaster raycaster;
	for (auto& enemy : *enemyManager.getEnemyList()) {
		RayCastResult ray = raycaster.rayCast(player.angle, player.position, map);
		bool wasWallShot = ray.depth < enemy.sprite->getDistanceFromPlayer(enemy.position, player);
		bool canTakeDamage = player.justShot and !wasWallShot and enemy.isAlive() and enemy.sprite->isOnScreenCenter;
		if (canTakeDamage){
			int damage = player.weapon->damage;
			enemy.takeDamage(damage);
		}
	}
	player.justShot = false;
}
