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
	itemManager = ItemManager::getInstance();
	currentLevel = 0;
	map = Map::getInstance();
	player = Player::getInstance();
	currentState = mainMenu;
}

void Game::initGame()
{
	itemManager->initItems();
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
	newState = canvas.draw(*map, *player, *itemManager, enemyManager, currentState);
}

void Game::logic()
{
	if (newState != na) 
	{
		currentState = newState;
	}

	Sound theme = soundMgr->getSound("main_menu.mp3");
	if (currentState == mainMenu and not IsSoundPlaying(theme)) {
		PlaySound(theme);
	}
	else if (currentState != mainMenu) {
		StopSound(theme);
	}
	

	switch (currentState) {
		case mainMenu:
			initGame();
			break;
		case playing:
			playCurrentSong();
			player->act(*map);
			itemManager->checkForPickup();
			enemyManager.runEnemyBehaviour(*player, *map);
			if (enemyManager.areEnemiesDead()) {
				nextLevel();
			}

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

void Game::playCurrentSong()
{
	Sound currentSong = soundMgr->getSound("");
	switch (map->getCurrentIndex()) {
		case 0:
			currentSong = soundMgr->getSound("level1.mp3");
			break;
	}
	if (!IsSoundPlaying(currentSong)) {
		SetSoundVolume(currentSong, 0.7);
		PlaySound(currentSong);
	}
}

void Game::nextLevel()
{
	currentLevel++;
	map->setLevel(currentLevel);
	itemManager->setLevel(currentLevel);
}
