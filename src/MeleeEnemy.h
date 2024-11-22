#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
public:
	void attack() override;
	void takeDamage(int damage) override;
	MeleeEnemy(Point2D position);
};
