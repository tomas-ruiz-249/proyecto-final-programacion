#include "MeleeEnemy.h"
#include "Player.h"
#include "SoundManager.h"
#include <iostream>

void MeleeEnemy::attack()
{
	Player* player = Player::getInstance();
	if (sprite->getDistanceFromPlayer(sprite->position, *player) <= 0.5 && player->isAlive() && !player->hurt) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound EnemyAttackSound = soundManager->getSound("demon_attack.mp3"); //sonido de ataque
		if (!IsSoundPlaying(EnemyAttackSound)) {
			PlaySound(EnemyAttackSound);
		}
		player->takeDamage(damage);
	}
}

void MeleeEnemy::takeDamage(int damage)
{
	Enemy::takeDamage(damage);
	if (isAlive()) {
		Sound hurt = SoundManager::getInstance()->getSound("demon_hurt.mp3");
		SetSoundVolume(hurt, 1);
		PlaySound(hurt);
	}
	if (!isAlive()) {
		Sound dead = SoundManager::getInstance()->getSound("demon_death.mp3");
		SetSoundVolume(dead, 1);
		PlaySound(dead);
	}
}

MeleeEnemy::MeleeEnemy(Point2D position)
{
	this->position = position;
	speed = 4;
}
