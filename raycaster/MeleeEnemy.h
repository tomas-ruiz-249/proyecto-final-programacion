#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
public:
	void attack() override;
	MeleeEnemy(Point2D position);
};
