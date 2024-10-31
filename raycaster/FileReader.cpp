#define _CRT_SECURE_NO_WARNINGS
#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring> 

using namespace std;

bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE])
{
    return false;
}

bool FileReader::readObjectsFromFile(const char* object_data, vector<Object>& objectList) {
    ifstream file(object_data);
    if (!file.is_open())
    {
        cerr << "No se pudo abrir el archivo: " << object_data << endl;
        return false;
    }

    string header;
    getline(file, header); 

    string line;
    while (getline(file, line))
    {
        char * c = const_cast<char*>(line.c_str());
        char * token = strtok(c, ","); 

        ObjectType type = ObjectType();
        Point2D position = { 0.0, 0.0 };
        double scale = 0.0;
        double shift = 0.0;

        for (int cont_col = 0; token != NULL; cont_col++)
        {
            switch (cont_col)
            {
            case 0:
                type = static_cast<ObjectType>(stoi(token));
                break;
            case 1:
                position.x = stod(token);
                break;
            case 2:
                position.y = stod(token); 
                break;
            case 3:
                scale = stod(token); 
                break;
            case 4:
                shift = stod(token);
                break;
            }
            token = strtok(NULL, ","); 
        }

        Object obj(type, position, scale, shift);
        objectList.push_back(obj);
    }

    file.close();
    return true;
}
