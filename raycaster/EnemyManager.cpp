#include "EnemyManager.h"
#include "FileReader.h"

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
