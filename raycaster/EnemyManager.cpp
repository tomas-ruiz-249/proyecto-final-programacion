#include "EnemyManager.h"
#include "FileReader.h"
#include "RayCaster.h"
#include <iostream>

std::vector<Enemy>* EnemyManager::getEnemyList()
{
    return &enemyList;
}

void EnemyManager::initEnemies()
{
    FileReader::readEnemiesFromFile("enemy_data.csv", enemyList);
}

void EnemyManager::clearEnemies()
{
    enemyList.clear();
}

void EnemyManager::runEnemyBehaviour(Player& player, Map map)
{
	RayCaster raycaster;
	RayCastResult ray;
	bool wasWallShot;
	bool canTakeDamage;
	for (auto& enemy : enemyList) {
		enemy.act(map);
		damageEnemy(enemy, player, map);
		setEnemyState(enemy);
	}
	player.justShot = false;
}

void EnemyManager::damageEnemy(Enemy& enemy, Player player, Map map)
{
	RayCaster raycaster;
	RayCastResult ray;
	bool wasWallShot;
	bool canTakeDamage;
	ray = raycaster.rayCast(player.angle, player.position, map);
	wasWallShot = ray.depth < enemy.sprite->getDistanceFromPlayer(enemy.position, player);
	canTakeDamage = player.justShot and !wasWallShot and enemy.isAlive() and enemy.sprite->isOnScreenCenter;
	if (canTakeDamage){
		int damage = player.weapon->damage;
		enemy.takeDamage(damage);
	}
	setEnemyState(enemy);
}

void EnemyManager::setEnemyState(Enemy& enemy)
{
	if (enemy.isAlive() and enemy.hurt) {
		enemy.sprite->animationIndex = 1;
		auto& anim = enemy.sprite->animations[enemy.sprite->animationIndex];
		if (anim.isAnimationDone()) {
			anim.resetAnimation();
			enemy.hurt = false;
		}
	}
	else {
		if (!enemy.isAlive()) {
			enemy.sprite->animationIndex = 2;
			auto& deathAnimation = enemy.sprite->animations[enemy.sprite->animationIndex];
			if (deathAnimation.isAnimationDone()) {
				deathAnimation.stop = true;
			}
		}
		else {
			enemy.sprite->animationIndex = 0;
		}
	}
}
