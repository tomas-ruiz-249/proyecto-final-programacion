#include "MeleeEnemy.h"
#include "Player.h"
#include "SoundManager.h"

void MeleeEnemy::attack()
{
	Player* player = Player::getInstance();
	if (sprite->getDistanceFromPlayer(sprite->position, *player) <= 0.5 and player->isAlive() and !player->hurt) {
		SoundManager* soundManager = SoundManager::getInstance();
		Sound EnemyAttackSound = soundManager->getSound("EnemyAttack.mp3"); //sonido de ataque
		PlaySound(EnemyAttackSound);
		player->takeDamage(damage);
	}
}

MeleeEnemy::MeleeEnemy(Point2D position)
{
	this->position = position;
}
