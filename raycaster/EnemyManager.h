#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {
public:
	std::vector<Enemy>* getEnemyList();
	void initEnemies();
	void clearEnemies();
private:
	std::vector<Enemy> enemyList;
};
