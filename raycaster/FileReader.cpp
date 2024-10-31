#define _CRT_SECURE_NO_WARNINGS
#include "FileReader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring> 

using namespace std;

bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE]) {
    std::ifstream file(fileName); //"map.txt"
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo de mapa.\n";
        return false;
    }

    std::string line;
    int row = 0;

    while (getline(file, line) && row < GRID_SIZE) {
        std::stringstream ss(line);
        std::string value;
        int col = 0;

        while (getline(ss, value, ',') && col < GRID_SIZE) {
            map[row][col] = stoi(value);
            col++;
        }
        row++;
    }

    file.close();
    return true; 
};

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
