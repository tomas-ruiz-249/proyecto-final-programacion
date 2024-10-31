#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

const int GRID_SIZE = 100; 


class Object {
private:
    int param1;
    int param2;
    int param3;

public:
    Object(int p1, int p2, int p3) : param1(p1), param2(p2), param3(p3) {}

    void print() const {
        cout << "Object(" << param1 << ", " << param2 << ", " << param3 << ")\n";
    }
};


class FileReader {
public:
    bool readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE]) {
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
    }

    bool readObjectsFromFile(const char* fileName, vector<Object>& objectList) {
        ifstream file(fileName); //"objects.txt"
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo de objetos.\n";
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int param1, param2, param3;

            ss >> param1 >> param2 >> param3;

            Object obj(param1, param2, param3);
            objectList.push_back(obj);
        }

        file.close();
        return true;
    }
};
