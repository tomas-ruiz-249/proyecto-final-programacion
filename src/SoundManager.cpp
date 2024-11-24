#include "SoundManager.h"
#include <iostream>

Sound SoundManager::getSound(std::string fileName)
{
    auto dir = getSoundsDir().append("/");
    dir.append(fileName);
    return (*soundList)[dir];
}

void SoundManager::loadSounds()
{
    std::string soundDir = getSoundsDir();
    if (DirectoryExists(soundDir.c_str())) {
        FilePathList files = LoadDirectoryFiles(soundDir.c_str());
        for(int i = 0; i < files.count; i++){
            normalizePathSeparator(files.paths[i]);
        }
        for (int i = 0; i < files.count; i++) {
            Sound sound = LoadSound(files.paths[i]);
            (*soundList)[files.paths[i]] = sound;
        }
    }
}

SoundManager* SoundManager::getInstance()
{
    if (!instance) {
        instance = new SoundManager();
    }
    return instance;
}

std::string SoundManager::getSoundsDir()
{
    return std::string("assets/sounds");
}

void SoundManager::normalizePathSeparator(char *path)
{
    for (int i = 0; path[i] != '\0'; i++) {
        if (path[i] == '\\') path[i] = '/';
    }
}

SoundManager::SoundManager() {
    soundList = new std::map<std::string, Sound>;
}

SoundManager* SoundManager::instance;
