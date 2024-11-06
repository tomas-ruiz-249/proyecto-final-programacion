#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "FileReader.h"
#include "Animated.h"
#include "TextureManager.h"

bool FileReader::readMapFromFile(const char* fileName, int map[GRID_SIZE][GRID_SIZE]) {
    std::string path("assets\\data\\");
    path.append(fileName);
    std::ifstream file(path); 
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
    std::string path("assets\\data\\");
    path.append(fileName);

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir el archivo: " << fileName << std::endl;
        return false;
    }

    std::string header;
    getline(file, header); 

    TextureManager* texMgr = TextureManager::getInstance();

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

        switch (obj.type) {
			case health: {
                Drawable* healthSprite = new Drawable();
                healthSprite->scale = 0.29;
                healthSprite->shift = 1.4;
                healthSprite->position = obj.position;
                healthSprite->tex = texMgr->getTexture("sprites\\static\\health.png");
                obj.sprite = healthSprite;
                break;
            }
			case ammo:{
                Drawable* ammoSprite = new Drawable();
				ammoSprite->scale = 0.29;
				ammoSprite->shift = 1.48;
                ammoSprite->position = obj.position;
                ammoSprite->tex = texMgr->getTexture("sprites\\static\\ammo.png");
                obj.sprite = ammoSprite;
                break;
            }
			case lamp:{
                //animated object
                Animated* lampSprite = new Animated();
                lampSprite->scale = 1.2;
                lampSprite->shift = -0.05;
                lampSprite->animationIndex = 1;
                lampSprite->position = obj.position;
                lampSprite->tex = texMgr->getTexture("");

                //create animations for animated
                Animation red = {};
                red.numFrames = 4;
                red.animationSpeed = 0.0009;
                red.texture = texMgr->getTexture("sprites\\animated\\lamp.png");
                lampSprite->animations.push_back(red);

				Animation green = {};
                green.numFrames = 4;
                green.animationSpeed = 0.0009;
                green.texture = texMgr->getTexture("sprites\\animated\\lamp_green.png");
                lampSprite->animations.push_back(green);
                obj.sprite = lampSprite;
                break;
            }
            default:{
                Drawable* undefined = new Drawable;
                undefined->scale = 1;
                undefined->shift = 0;
                undefined->position = obj.position;
            }
        }
        objectList.push_back(obj);
    }

    file.close();
    return true;
}
