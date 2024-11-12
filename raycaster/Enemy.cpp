#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "RayCaster.h"

void Enemy::act(Map& map)
{
	if (isAlive()) {
		move(map);
		attack();
	}
}

void Enemy::takeDamage(int damage)
{
	hurt = true;
	health -= damage;
}

void Enemy::attack()
{
}

void Enemy::move(Map map)
{
	Player player = *Player::getInstance();
	RayCaster rayCaster;

	Point2D targetPos = player.position;
	angle = atan2(targetPos.y - position.y , targetPos.x - position.x);
	Point2D d;
	d.x = cos(angle) * speed * GetFrameTime();
	d.y = sin(angle) * speed * GetFrameTime();
	double distanceFromPlayer = sprite->getDistanceFromPlayer(position, player);
	if (map.isPositionEmpty(int(position.y + d.y), int(position.x)) and distanceFromPlayer > 0.5){
		position.y += d.y;
	}
	if (map.isPositionEmpty(int(position.y), int(position.x + d.x)) and distanceFromPlayer > 0.5) {
		position.x += d.x;
	}
}
