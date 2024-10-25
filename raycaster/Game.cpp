#include "Game.h"

void Game::startGame()
{
	canvas.startWindow();
	mainLoop();
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
