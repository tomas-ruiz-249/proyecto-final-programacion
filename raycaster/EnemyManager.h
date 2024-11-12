#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {
public:
	std::vector<Enemy>* getEnemyList();
	void initEnemies();
	void clearEnemies();
	void runEnemyBehaviour(Player& player, Map map);
private:
	void damageEnemy(Enemy& enemy, Player player, Map map);
	void setEnemyState(Enemy& enemy);
	std::vector<Enemy> enemyList;
};
