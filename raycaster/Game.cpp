#include "Game.h"

void Game::startGame()
{
	InitWindow(0, 0, "");
	int width = GetScreenWidth();
	int height = GetScreenHeight();
	CloseWindow();
	canvas = Canvas(width, height);
	canvas.startWindow();
	mainLoop();
}

Game::Game()
{
	map = Map();
	canvas = Canvas();
	player = Player();
}

void Game::mainLoop()
{
	std::string fps;
	while (!WindowShouldClose()) {
		fps = std::to_string(GetFPS());
		SetWindowTitle(fps.c_str());

		player.move(map);
		canvas.draw(map, player);
	}
}
