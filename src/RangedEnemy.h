#pragma once
#include "Enemy.h"
#include "Item.h"
#include "Projectile.h"

class RangedEnemy : public Enemy {
public:
	void act(Map& map) override;
	void attack() override;
	void move(Map& map) override;
	void takeDamage(int damage) override;
	std::vector<Projectile*> getProjectiles();
	RangedEnemy(Point2D position);
private:
	std::vector<Projectile*> projectiles;
	bool attacking;
	double attackTimer;
	double attackCoolDown;
	void checkForProjectileColision();
};
