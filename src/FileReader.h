#pragma once
#include <vector>
#include "Map.h"
#include "Item.h"
#include "Enemy.h"

class FileReader {
public:
    static bool readMapFromFile(const char* fileName, WallType ** map);
    static bool readItemsFromFile(const char* fileName, std::vector<Item*>& ItemList);
    static bool readEnemiesFromFile(const char* fileName, std::vector<Enemy*>& enemyList);
};
