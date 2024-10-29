#pragma once
#include <vector>
#include "Object.h"

class ObjectManager {
public:
	std::vector<Object> getObjectList();
private:
	std::vector<Object> objectList;
};
