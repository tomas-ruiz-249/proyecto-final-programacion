#pragma once
enum WallType {
	none = 0,
	brick = 1,
	stone = 2,
	mossyStone = 3
};

enum ObjectType {
	invalid = 0,
	health = 1,
	ammo = 2,
	lamp = 3,
};

enum EnemyType {
	melee = 1,
	range = 2,
};

enum GameState {
	mainMenu = 0,
	playing = 1,
	gameOver = 2,
	pause = 3
};
