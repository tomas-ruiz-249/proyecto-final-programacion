#define _CRT_SECURE_NO_WARNINGS
#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring> 

bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE])
{
    return false;
}

bool FileReader::readObjectsFromFile(const char* fileName, std::vector<Object>& objectList) {
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << fileName << std::endl;
        return false;
    }

    std::string header;
    getline(file, header); 

    std::string line;
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
                type = static_cast<ObjectType>(std::stoi(token));
                break;
            case 1:
                position.x = std::stod(token);
                break;
            case 2:
                position.y = std::stod(token); 
                break;
            }
            token = strtok(NULL, ","); 
        }

        Object obj(type, position);
        objectList.push_back(obj);
    }

    file.close();
    return true;
}
