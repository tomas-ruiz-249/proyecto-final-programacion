#include "ObjectManager.h"

std::vector<Object> ObjectManager::getObjectList()
{
    return objectList;
}

void ObjectManager::initObjects()
{
    FileReader::readObjectsFromFile("assets\\data\\object_data.csv", objectList);
}

void ObjectManager::clearObjects()
{
    objectList.clear();
}
