#include "Game.h"
#include <iostream>

void Game::startGame()
{
	objManager.initObjects();
	enemyManager.initEnemies();
	mainLoop();
}

GameState Game::getState()
{
	return state;
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
	state = mainMenu;
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
	canvas.draw(*map, *player, objManager, enemyManager, state);
}

void Game::logic()
{
	switch (state) {
		case mainMenu:
			//empezar juego si se toca cualquier tecla
			if (GetKeyPressed()) {
				state = playing;
			}
			break;
		case playing:
			//correr juego normalmente
			player->act(*map);
			objManager.checkForPickup();
			enemyManager.runEnemyBehaviour(*player, *map);

			//pausar juego si se presiona p y causar game over si jugador muere
			if (IsKeyPressed(KEY_P) and player->isAlive()) {
				state = pause;
			}
			if (not player->isAlive()) {
				state = gameOver;
			}
			break;
		case pause:
			//renaudar juego al presionar p
			if (IsKeyPressed(KEY_P)) {
				state = playing;
			}
			break;
		case gameOver:
			//reiniciar juego si se presiona una tecla despues de morir
			if (GetKeyPressed()) {
				state = mainMenu;
				player->reset();
				startGame();
			}
			break;
	}
}
