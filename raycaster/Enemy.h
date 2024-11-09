#pragma once
#include "Entity.h"
#include "Animated.h"
#include "Enumerations.h"

class Enemy : public Entity {
public:
	Animated* sprite;
	EnemyType type;
	void act(Map& map) override;
	void takeDamage() override;
};
