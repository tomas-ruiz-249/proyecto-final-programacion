#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "RayCaster.h"

void Enemy::act(Map& map)
{
	if (isAlive()) {
		if (!hurt) {
			move(map);
			attack();
		}
	}
}

void Enemy::takeDamage(int damage)
{
	hurt = true;
	if (health - damage < 0) {
		health = 0;
	}
	else {
		health -= damage;
	}
}


void Enemy::move(Map& map)
{
	Player player = *Player::getInstance();
	RayCaster rayCaster;

	Point2D targetPos = player.position;
	angle = atan2(targetPos.y - position.y , targetPos.x - position.x);
	Point2D d;
	d.x = cos(angle) * speed * GetFrameTime();
	d.y = sin(angle) * speed * GetFrameTime();

	RayCastResult ray = rayCaster.rayCast(angle, position, map);
	double distanceFromPlayer = sprite->getDistanceFromPlayer(position, player);
	//approach only if player is on sight
	if (distanceFromPlayer > 0.5 && ray.depth > distanceFromPlayer) {
		if (map.isPositionEmpty(int(position.y + d.y), int(position.x))){
			position.y += d.y;
		}
		if (map.isPositionEmpty(int(position.y), int(position.x + d.x))) {
			position.x += d.x;
		}
	}
}

Enemy::Enemy()
{
	damage = 10;
	health = 100;
}

Enemy::Enemy(int health,int damage): Entity(health)
{
	this->damage = damage;
}
