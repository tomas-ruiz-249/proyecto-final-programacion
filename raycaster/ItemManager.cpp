#include "ItemManager.h"
#include "AmmoBox.h"
#include "HealthBox.h"
#include <iostream>

std::vector<Item*>* ItemManager::getCurrentItemList()
{
    std::vector<Item*>* ptr = &currentItems;
    return ptr;
}

void ItemManager::initItems()
{
	currentItems.clear();
	itemLists.clear();
	FilePathList itemPaths = LoadDirectoryFiles("assets\\data\\");
	for (int i = 0; i < itemPaths.count; i++) {
		auto extension = GetFileExtension(itemPaths.paths[i]);
		if (std::string(extension) == ".csv") {
			std::vector<Item*> newItemList;
			if (FileReader::readItemsFromFile(itemPaths.paths[i], newItemList)) {
				itemLists.push_back(newItemList);
			}
		}
	}
	currentLevel = 0;
	currentItems = itemLists[currentLevel];
}

void ItemManager::clearItems()
{
    currentItems.clear();
}

void ItemManager::checkForPickup()
{
    double dist = 0;
    int counter = 0;
	for (auto it = currentItems.begin(); it != currentItems.end();) {
		auto obj = *it;
		dist = obj->sprite->getDistanceFromPlayer(obj->position, *Player::getInstance());
		if (dist < 0.5) {
			auto ammoPtr = dynamic_cast<AmmoBox*>(obj);
			auto healthPtr = dynamic_cast<HealthBox*>(obj);

			if (ammoPtr) {
				if (ammoPtr->pickup()) {
					delete ammoPtr->sprite;
					delete ammoPtr;
					it = currentItems.erase(it); 
					continue; 
				}
			} else if (healthPtr) {
				if (healthPtr->pickup()) {
					delete healthPtr->sprite;
					delete healthPtr;
					it = currentItems.erase(it); 
					continue; 
				}
			}
		}
		++it; 
	}
}

int ItemManager::getCurrentLevel()
{
	return currentLevel;
}

void ItemManager::setLevel(int level)
{
	if (level < itemLists.size()) {
		currentLevel = level;
		currentItems = itemLists[currentLevel];
	}
}

ItemManager* ItemManager::instance;

ItemManager* ItemManager::getInstance()
{
	if (!instance) {
		instance = new ItemManager();
	}
	return instance;
}

ItemManager::ItemManager()
{
	currentLevel = 0;
	initItems();
	currentItems = itemLists[currentLevel];
}