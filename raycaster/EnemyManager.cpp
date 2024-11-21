#include "EnemyManager.h"
#include "FileReader.h"
#include "RayCaster.h"
#include <iostream>
#include "SoundManager.h"
#include "ItemManager.h"
#include "Lamp.h"
#include "RangedEnemy.h"
#include "MeleeEnemy.h"
#include "TextureManager.h"

std::vector<Enemy*>* EnemyManager::getEnemyList()
{
    return &enemyList;
}

void EnemyManager::initEnemies()
{
	clearEnemies();
	ItemManager* itMgr = ItemManager::getInstance();
	TextureManager* texMgr = TextureManager::getInstance();
	auto itemList = itMgr->getCurrentItemList();
	for (auto item : *itemList) {
		Lamp* lampPtr = dynamic_cast<Lamp*>(item);
		if (lampPtr) {
			EnemyType type = EnemyType(itMgr->getCurrentLevel() % 2 + 1);
			Point2D pos = lampPtr->position;
			switch (type) {
                case melee:
                {
                    MeleeEnemy* enemy = new MeleeEnemy(pos);
                    enemy->speed = 4;
                    enemy->sprite = new Animated();
                    enemy->sprite->tex = texMgr->getTexture("");
                    enemy->sprite->animationIndex = 0;
                    enemy->sprite->scale = 0.9;
                    enemy->sprite->shift = 0.1;
                    enemy->sprite->position = enemy->position;

                    Animation walk = {};
                    walk.texture = texMgr->getTexture("sprites\\animated\\demon_walk.png");
                    walk.numFrames = 4;
                    walk.animationSpeed = 7.0;

                    Animation hurt = {};
                    hurt.texture = texMgr->getTexture("sprites\\animated\\demon_hurt.png");
                    hurt.numFrames = 5;
                    hurt.animationSpeed = 5.0;

                    Animation death = {};
                    death.texture = texMgr->getTexture("sprites\\animated\\demon_death.png");
                    death.numFrames = 7;
                    death.animationSpeed = 3.5;

                    enemy->sprite->animations.push_back(walk);
                    enemy->sprite->animations.push_back(hurt);
                    enemy->sprite->animations.push_back(death);
                    enemyList.push_back(enemy);
                    break;
                }
				case range:
				{
					RangedEnemy* enemy = new RangedEnemy(pos);
					enemy->speed = 2;
					enemy->sprite = new Animated();
					enemy->sprite->tex = texMgr->getTexture("");
					enemy->sprite->animationIndex = 0;
					enemy->sprite->scale = 1;
					enemy->sprite->shift = 0;
					enemy->sprite->position = enemy->position;

					Animation walk = {};
					walk.texture = texMgr->getTexture("sprites\\animated\\zombie_walk.png");
					walk.numFrames = 4;
					walk.animationSpeed = 9.0;
					enemy->sprite->animations.push_back(walk);

					Animation hurt = {};
					hurt.texture = texMgr->getTexture("sprites\\animated\\zombie_hurt.png");
					hurt.numFrames = 4;
					hurt.animationSpeed = 8.0;
					enemy->sprite->animations.push_back(hurt);

					Animation death = {};
					death.texture = texMgr->getTexture("sprites\\animated\\zombie_death.png");
					death.numFrames = 7;
					death.animationSpeed = 9.0;
					enemy->sprite->animations.push_back(death);
					enemyList.push_back(enemy);
				}
			}
		}
	}
}

void EnemyManager::clearEnemies()
{
	for (auto& enemy : enemyList) {
		delete enemy;
	}
    enemyList.clear();
}

void EnemyManager::runEnemyBehaviour(Player& player, Map map)
{
	RayCaster raycaster;
	RayCastResult ray;
	for (auto enemy : enemyList) {
		enemy->act(map);
		damageEnemy(enemy, player, map);
		setEnemyState(enemy);
	}
	player.justShot = false;
}

bool EnemyManager::areEnemiesDead()
{
	for (auto& enemy : enemyList) {
		if (enemy->isAlive()) {
			return false;
		}
	}
	return true;
}

void EnemyManager::damageEnemy(Enemy* enemy, Player player, Map map)
{
	RayCaster raycaster;
	RayCastResult ray;
	bool wasWallShot;
	bool canTakeDamage;
	ray = raycaster.rayCast(player.angle, player.position, map);
	wasWallShot = ray.depth < enemy->sprite->getDistanceFromPlayer(enemy->position, player);
	canTakeDamage = player.justShot and !wasWallShot and enemy->isAlive() and enemy->sprite->isOnScreenCenter;
	if (canTakeDamage){
		int range = player.weapon->getRange();
		int damage = player.weapon->getDamage() * (range - enemy->sprite->getDistanceFromPlayer(enemy->position, player))/range;
		if (damage < 0) {
			damage = 0;
		}
		enemy->takeDamage(damage);
	}
	setEnemyState(enemy);
}

void EnemyManager::setEnemyState(Enemy* enemy)
{
	if (enemy->isAlive() and enemy->hurt) {
		enemy->sprite->animationIndex = 1;
		auto& anim = enemy->sprite->animations[enemy->sprite->animationIndex];
		if (anim.isAnimationDone()) {
			anim.resetAnimation();
			enemy->hurt = false;
		}
	}
	else {
		if (!enemy->isAlive()) {
			enemy->sprite->animationIndex = 2;
			auto& deathAnimation = enemy->sprite->animations[enemy->sprite->animationIndex];
			if (deathAnimation.isAnimationDone()) {
				deathAnimation.stop = true;
			}
		}
		else {
			enemy->sprite->animationIndex = 0;
		}
	}
}
