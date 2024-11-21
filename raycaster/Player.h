#pragma once
#include "Entity.h"
#include "Weapon.h"


class Player : public Entity {
public:
	Weapon* weapon;
	bool justShot;
	void act(Map& map) override;
	void move(Map& map) override;
	void takeDamage(int damage) override;
	void attack() override;
	bool heal(int healthPoints);
	void reset();
	void setSensibility(double sensibility);
	double getSensibility();
	int getMaxHealth();
	static Player* getInstance();
	friend class HealthBox;
private:
	int maxHealth;
	double sensibility;
	double hurtTimer;
	static Player* player;
	Player();
};
