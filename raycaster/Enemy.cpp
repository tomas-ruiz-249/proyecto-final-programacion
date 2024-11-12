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
	Player* player = Player::getInstance();
	std::cout << sprite->getDistanceFromPlayer(sprite->position, *player) << "\n";
	if (sprite->getDistanceFromPlayer(sprite->position, *player) <= 0.5 and player->isAlive() and !player->hurt) {
		player->takeDamage(damage);
	}
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

	RayCastResult ray = rayCaster.rayCast(angle, position, map);
	double distanceFromPlayer = sprite->getDistanceFromPlayer(position, player);
	if (distanceFromPlayer > 0.5 and ray.depth > distanceFromPlayer) {
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

Enemy::Enemy(int damage)
{
	health = 100;
	this->damage = damage;
}
