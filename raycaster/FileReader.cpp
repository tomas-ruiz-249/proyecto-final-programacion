#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "FileReader.h"

using namespace std;




bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE]) {
    ifstream file(fileName); //"map.txt"
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de mapa.\n";
        return false;
    }

    string line;
    int row = 0;

    while (getline(file, line) && row < GRID_SIZE) {
        stringstream ss(line);
        string value;
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
