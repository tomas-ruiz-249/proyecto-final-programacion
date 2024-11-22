#pragma once
enum WallType {
	none = 0,
	brick = 1,
	stone = 2,
	mossyStone = 3,
	closedDoor = 4,
	openDoor = 6,
};

enum ItemType {
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
	pause = 3,
	options = 4,
	na = 5,
	end = 6,
	transition = 7,
};
