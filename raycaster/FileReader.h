#pragma once
#include <vector>
#include "Map.h"
#include "Object.h"
using namespace std;

class FileReader {
public:
    static bool readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE]);
    static bool readObjectsFromFile(const char * object_data, vector<Object>& objectList);
};
