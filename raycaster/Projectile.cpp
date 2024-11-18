#include "Projectile.h"
#include "TextureManager.h"
#include "RayCaster.h"
#include <iostream>

Projectile::Projectile(Point2D pos, double ang, int damage)
{
	position = pos;
	speed = 10;
	angle = ang;
	timer = 0;
	timeLimit = 3;
	this->damage = damage;

	sprite = new Animated();
	sprite->scale = 0.5;
	sprite->shift = 0;

	TextureManager* texMgr = TextureManager::getInstance();
	Animation fireball = {};
	fireball.texture = texMgr->getTexture("sprites\\animated\\fireball.png");
	fireball.numFrames = 2;
	fireball.animationSpeed = 2;
	sprite->animations.push_back(fireball);
}

bool Projectile::shoot()
{
	RayCaster raycaster;
	Player* player = Player::getInstance();
	Map map = *Map::getInstance();

	RayCastResult rayToWall = raycaster.rayCast(angle, position, map);
	double distanceToPlayer = sprite->getDistanceFromPlayer(position, *player);

	bool projectileCrash = distanceToPlayer < 0.5 or rayToWall.depth < 0.5 or timer > timeLimit;
	if (projectileCrash) {
		if (distanceToPlayer < 0.5) {
			player->takeDamage(damage);
		}
		return true;
	}
	else {
		Point2D d;
		d.x = cos(angle) * speed * GetFrameTime();
		d.y = sin(angle) * speed * GetFrameTime();
		position.x += d.x;
		position.y += d.y;
		timer += GetFrameTime();
		return false;
	}
}

Point2D Projectile::getPosition()
{
	return position;
}
