#pragma once
#include <raylib.h>
#include <map>
#include <string>

class TextureManager {
public:
	Texture getTexture(std::string texture);
	void loadTexturesToVRAM();
	static TextureManager* getInstance();
private:
	static TextureManager* instance;
	std::map<std::string, Texture> *textures;
	std::string getTextureDir();
	TextureManager();
};
