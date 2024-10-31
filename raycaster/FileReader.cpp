#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE])
{
    //juanjose
    return false;
}


bool FileReader::readObjectsFromFile(const char * fileName, vector<Object>& objectList) {

    ifstream file(fileName);
    if (!file.is_open()) 
    {
        return false;
    }

    string line;
    while (getline(file, line)) 
    {
        stringstream strstre(line);
        string item;

        ObjectType type;
        Point2D position;
        double scale, shift;

        if (getline(strstre, item, ','))
        {
            type = static_cast<ObjectType>(stoi(item));
        }

        if (getline(strstre, item, ','))
        {
            position.x = stod(item);
        }

        if (getline(strstre, item, ','))
        {
            position.y = stod(item);
        }

        if (getline(strstre, item, ','))
        {
            scale = stod(item);
        }

        if (getline(strstre, item, ','))
        {
            shift = stod(item);
        }

        Object obj(type, position, scale, shift);
        objectList.push_back(obj);
    }
    file.close();
    return true;
}
