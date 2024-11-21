#pragma once
#include <vector>
#include "Item.h"
#include "FileReader.h"

class ItemManager {
public:
	std::vector<Item*>* getCurrentItemList();
	void initItems();
	void clearItems();
	void checkForPickup();
	int getCurrentLevel();
	void setLevel(int level);
	static ItemManager* getInstance();
private:
	int currentLevel;
	std::vector<std::vector<Item*>> itemLists;
	std::vector<Item*> currentItems;
	static ItemManager* instance;
	ItemManager();
};
