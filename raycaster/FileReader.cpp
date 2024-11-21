#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "FileReader.h"
#include "Animated.h"
#include "TextureManager.h"
#include "HealthBox.h"
#include "AmmoBox.h"
#include "Lamp.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"

bool FileReader::readMapFromFile(const char* fileName, WallType** map) {
    std::string path(fileName);
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
            map[row][col] = (WallType)stoi(value);
            col++;
        }
        row++;
    }

    file.close();
    return true; 
};

bool FileReader::readItemsFromFile(const char* fileName, std::vector<Item*>& itemList) {
    std::string path(fileName);
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

        ItemType type = invalid;
        Point2D position = { 0.0, 0.0 };

        for (int cont_col = 0; token != NULL; cont_col++)
        {
            switch (cont_col)
            {
            case 0:
                type = static_cast<ItemType>(std::stoi(token));
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

        Item* item;

        switch (type) {
			case health: {
                HealthBox* health = new HealthBox(position);
                Drawable* healthSprite = new Drawable();
                healthSprite->scale = 0.29;
                healthSprite->shift = 1.4;
                healthSprite->position = health->position;
                healthSprite->tex = texMgr->getTexture("sprites\\static\\health.png");
                health->sprite = healthSprite;
                item = health;
                break;
            }
			case ammo:{
                AmmoBox* ammo = new AmmoBox(position);
                Drawable* ammoSprite = new Drawable();
				ammoSprite->scale = 0.29;
				ammoSprite->shift = 1.48;
                ammoSprite->position = ammo->position;
                ammoSprite->tex = texMgr->getTexture("sprites\\static\\ammo.png");
                ammo->sprite = ammoSprite;
                item = ammo;
                break;
            }
			case lamp:{
                Lamp* lamp = new Lamp(position);
                Animated* lampSprite = new Animated();
                lampSprite->scale = 1.2;
                lampSprite->shift = -0.05;
                lampSprite->animationIndex = 0;
                lampSprite->position = lamp->position;
                lampSprite->tex = texMgr->getTexture("");

                Animation red = {};
                red.numFrames = 4;
                red.animationSpeed = 2.0;
                red.texture = texMgr->getTexture("sprites\\animated\\lamp.png");

				Animation green = {};
                green.numFrames = 4;
                green.animationSpeed = 2.0;
                green.texture = texMgr->getTexture("sprites\\animated\\lamp_green.png");

                lampSprite->animations.push_back(red);
                lampSprite->animations.push_back(green);

                lamp->sprite = lampSprite;
                item = lamp;
                break;
            }
            default:{
                std::cout << "could not instanciate item\n";
                break;
            }
        }
        itemList.push_back(item);
    }

    file.close();
    return true;
}

bool FileReader::readEnemiesFromFile(const char* fileName, std::vector<Enemy*>& enemyList)
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

            EnemyType type;
            Point2D pos = {};
            token = strtok(const_cast<char*>(line.c_str()), ",");

            while (token != NULL && counter < 3) {
				switch (counter) {
					case 0:
						type = (EnemyType)std::stoi(token);
						break;
					case 1:
						pos.x = (double)std::stoi(token);
						break;
					case 2:
						pos.y = (double)std::stoi(token);
						break;
				}
                token = strtok(nullptr, ",");
                counter++;
            }
            counter = 0;

            switch (type) {
                case melee:
                {
                    MeleeEnemy* enemy = new MeleeEnemy(pos);
                    enemy->speed = 4;
                    enemy->sprite = new Animated();
                    enemy->sprite->tex = texMgr->getTexture("");
                    enemy->sprite->animationIndex = 0;
                    enemy->sprite->scale = 0.9;
                    enemy->sprite->shift = 0.1;
                    enemy->sprite->position = enemy->position;

                    Animation walk = {};
                    walk.texture = texMgr->getTexture("sprites\\animated\\demon_walk.png");
                    walk.numFrames = 4;
                    walk.animationSpeed = 7.0;

                    Animation hurt = {};
                    hurt.texture = texMgr->getTexture("sprites\\animated\\demon_hurt.png");
                    hurt.numFrames = 5;
                    hurt.animationSpeed = 5.0;

                    Animation death = {};
                    death.texture = texMgr->getTexture("sprites\\animated\\demon_death.png");
                    death.numFrames = 7;
                    death.animationSpeed = 3.5;

                    enemy->sprite->animations.push_back(walk);
                    enemy->sprite->animations.push_back(hurt);
                    enemy->sprite->animations.push_back(death);
                    enemyList.push_back(enemy);
                    break;
                }
				case range:
                {
                    RangedEnemy* enemy = new RangedEnemy(pos);
                    enemy->speed = 2;
                    enemy->sprite = new Animated();
                    enemy->sprite->tex = texMgr->getTexture("");
                    enemy->sprite->animationIndex = 0;
                    enemy->sprite->scale = 1;
                    enemy->sprite->shift = 0;
                    enemy->sprite->position = enemy->position;

                    Animation walk = {};
                    walk.texture = texMgr->getTexture("sprites\\animated\\zombie_walk.png");
                    walk.numFrames = 4;
                    walk.animationSpeed = 9.0;
                    enemy->sprite->animations.push_back(walk);

                    Animation hurt = {};
                    hurt.texture = texMgr->getTexture("sprites\\animated\\zombie_hurt.png");
                    hurt.numFrames = 4;
                    hurt.animationSpeed = 8.0;
                    enemy->sprite->animations.push_back(hurt);

                    Animation death = {};
                    death.texture = texMgr->getTexture("sprites\\animated\\zombie_death.png");
                    death.numFrames = 7;
                    death.animationSpeed = 9.0;
                    enemy->sprite->animations.push_back(death);

                    enemyList.push_back(enemy);
                    break;
                }
            }
        }
        return true;
    }
    else {
        std::cout << "could not open file " << fileName << std::endl;
        return false;
    }
    return true;
}
