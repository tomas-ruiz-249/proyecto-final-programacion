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

        ObjectType type;
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
                lampSprite->animationIndex = 0;
                lampSprite->position = obj.position;
                lampSprite->tex = texMgr->getTexture("");

                //create animations for animated
                Animation red = {};
                red.numFrames = 4;
                red.animationSpeed = 2.0;
                red.texture = texMgr->getTexture("sprites\\animated\\lamp.png");
                lampSprite->animations.push_back(red);

				Animation green = {};
                green.numFrames = 4;
                green.animationSpeed = 2.0;
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

bool FileReader::readEnemiesFromFile(const char* fileName, std::vector<Enemy>& enemyList)
{
    std::string filePath("assets\\data\\");
    filePath.append(fileName);
    std::ifstream file(filePath);
    std::string line;
    char* token;
    int counter = 0;
    TextureManager* texMgr = TextureManager::getInstance();
    if (file.is_open()) {
        std::getline(file, line);
        while (std::getline(file, line)) {
            Enemy enemy;
            token = strtok(const_cast<char*>(line.c_str()), ",");
            while (token != NULL && counter < 3) {
				switch (counter) {
					case 0:
						enemy.type = (EnemyType)std::stoi(token);
						break;
					case 1:
						enemy.position.x = (double)std::stoi(token);
						break;
					case 2:
						enemy.position.y = (double)std::stoi(token);
						break;
				}
                token = strtok(nullptr, ",");
                counter++;
            }
            counter = 0;
            EnemyType& type = enemy.type;
            switch (type) {
				case demon:
                {
                    enemy.sprite = new Animated();
                    enemy.sprite->tex = texMgr->getTexture("");
                    enemy.sprite->animationIndex = 0;
                    enemy.sprite->scale = 1;
                    enemy.sprite->shift = 0;
                    enemy.sprite->position = enemy.position;

                    Animation idle = {};
                    idle.texture = texMgr->getTexture("sprites\\animated\\demon.png");
                    idle.numFrames = 4;
                    idle.animationSpeed = 5.0;
                    enemy.sprite->animations.push_back(idle);
                    break;
                }
                case imp:
                {
                    enemy.sprite = new Animated();
                    enemy.sprite->tex = texMgr->getTexture("");
                    enemy.sprite->animationIndex = 0;
                    enemy.sprite->scale = 0.9;
                    enemy.sprite->shift = 0.1;
                    enemy.sprite->position = enemy.position;

                    Animation idle = {};
                    idle.texture = texMgr->getTexture("sprites\\animated\\imp.png");
                    idle.numFrames = 4;
                    idle.animationSpeed = 7.0;
                    enemy.sprite->animations.push_back(idle);
                    break;
                }
            }
            enemyList.push_back(enemy);
        }
        return true;
    }
    else {
        std::cout << "could not open file " << fileName << std::endl;
        return false;
    }
    return true;
}
