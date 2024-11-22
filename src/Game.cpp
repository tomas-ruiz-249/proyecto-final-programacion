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
	currentSong = soundMgr->getSound("level1.mp3");
}

void Game::initGame()
{
	currentLevel = 0;
	map->setLevel(currentLevel);
	map->restoreMaps();
	itemManager->setLevel(currentLevel);
	itemManager->initItems();
	enemyManager.initEnemies();
	player->reset();
}

void Game::mainLoop()
{
	while (!WindowShouldClose()) {
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

	Sound menu = soundMgr->getSound("main_menu.mp3");
	Sound transitionMusic = soundMgr->getSound("transition.mp3");
	if (currentState == mainMenu and not IsSoundPlaying(menu)) {
		PlaySound(menu);
	}
	else if (currentState != mainMenu) {
		StopSound(menu);
	}

	if (currentState == transition and not IsSoundPlaying(transitionMusic)) {
		PlaySound(transitionMusic);
	}
	else if (currentState != transition) {
		StopSound(transitionMusic);
	}
	

	switch (currentState) {
		case mainMenu:
			initGame();
			if(IsSoundPlaying(currentSong)){
				StopSound(currentSong);
			}
			break;
		case playing:
			playCurrentSong();
			player->act(*map);
			itemManager->checkForPickup();
			enemyManager.runEnemyBehaviour(*player, *map);
			if (enemyManager.areEnemiesDead() or IsKeyPressed(KEY_M)) {
				currentState = transition;
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
		case transition:
			if (IsKeyPressed(KEY_ENTER) and map->getCurrentIndex() < map->getMapCount() - 1) {
				nextLevel();
				currentState = playing;
			}
			StopSound(currentSong);
			break;
	}
}

void Game::playCurrentSong()
{
	currentSong = soundMgr->getSound("");
	switch (map->getCurrentIndex()) {
		case 0:
			currentSong = soundMgr->getSound("level1.mp3");
			break;
		case 1:
			currentSong = soundMgr->getSound("level2.mp3");
			break;
	}
	if (!IsSoundPlaying(currentSong)) {
		SetSoundVolume(currentSong, 0.7);
		PlaySound(currentSong);
	}
}

void Game::nextLevel()
{
	if (map->getMapCount() - 1 > currentLevel) {
		currentLevel++;
		player->reset();
		map->setLevel(currentLevel);
		itemManager->setLevel(currentLevel);
		enemyManager.initEnemies();
	}
}
