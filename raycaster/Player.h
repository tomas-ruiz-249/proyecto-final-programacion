#pragma once
#include "Entity.h"
#include "Weapon.h"


class Player : public Entity {
public:
	Weapon* weapon;
	bool justShot;
	void act(Map& map) override;
	void move(Map map) override;
	void takeDamage(int damage) override;
	void attack() override;
	static Player* getInstance();
private:
	double hurtTimer;
	static Player* player;
	Player();
};
