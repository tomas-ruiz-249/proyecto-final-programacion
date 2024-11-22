#pragma once
#include <raylib.h>
#include <string>
#include <map>

class SoundManager {
public:
	Sound getSound(std::string fileName);
	void loadSounds();
	static SoundManager* getInstance();
private:
	std::map<std::string, Sound>* soundList;
	static SoundManager* instance;
	std::string getSoundsDir();
	SoundManager();
};
