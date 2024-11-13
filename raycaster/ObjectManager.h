#pragma once
#include <vector>
#include "Object.h"
#include "FileReader.h"

class ObjectManager {
public:
	std::vector<Object*>* getObjectList();
	void initObjects();
	void clearObjects();
	void checkForPickup();
private:
	std::vector<Object*> objectList;
};
