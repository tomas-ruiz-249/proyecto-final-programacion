#pragma once
#include "Entity.h"
#include "Weapon.h"


class Player : public Entity {
public:
	Weapon* weapon;
	bool justShot;
	void act(Map& map) override;
	void takeDamage(int damage) override;
	Player();
private:
};
