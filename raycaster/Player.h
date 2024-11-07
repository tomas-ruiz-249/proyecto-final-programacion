#pragma once
#include "Entity.h"
#include "Weapon.h"


class Player : public Entity {
public:
	Weapon* weapon;
	void move(Map& map) override;
	Player();
private:
};
