#pragma once
#include <raylib.h>
#include <map>
#include <string>

class TextureManager {
public:
	Texture getTexture(std::string texture);
	void loadTexturesToVRAM();
	TextureManager();
private:
	std::map<std::string, Texture> *textures;
	std::string getTextureDir();
};
