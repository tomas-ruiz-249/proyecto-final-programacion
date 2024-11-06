#include <iostream>
#include <string>
#include "TextureManager.h"

void TextureManager::loadTexturesToVRAM()
{
	std::string textureDir = getTextureDir();
	if (DirectoryExists(textureDir.c_str())) {
		std::string wallsDir = textureDir;
		wallsDir.append("walls");
		FilePathList wallTextures = LoadDirectoryFiles(wallsDir.c_str());
		for (int i = 0; i < wallTextures.count; i++) {
			Texture texture = LoadTexture(wallTextures.paths[i]);
			(*textures)[wallTextures.paths[i]] = texture;
		}

		std::string staticSpritesDir = textureDir;
		staticSpritesDir.append("sprites\\static");
		FilePathList staticSpriteTextures = LoadDirectoryFiles(staticSpritesDir.c_str());
		for (int i = 0; i < staticSpriteTextures.count; i++) {
			Texture texture = LoadTexture(staticSpriteTextures.paths[i]);
			(*textures)[staticSpriteTextures.paths[i]] = texture;
		}

		std::string animatedSpritesDir = textureDir;
		animatedSpritesDir.append("sprites\\animated");
		FilePathList animatedSpriteTextures = LoadDirectoryFiles(animatedSpritesDir.c_str());
		for (int i = 0; i < animatedSpriteTextures.count; i++) {
			Texture texture = LoadTexture(animatedSpriteTextures.paths[i]);
			(*textures)[animatedSpriteTextures.paths[i]] = texture;
		}

		std::string backgroundsDir = textureDir;
		backgroundsDir.append("backgrounds");
		FilePathList backgroundTextures = LoadDirectoryFiles(backgroundsDir.c_str());
		for (int i = 0; i < backgroundTextures.count; i++) {
			Texture texture = LoadTexture(backgroundTextures.paths[i]);
			(*textures)[backgroundTextures.paths[i]] = texture;
		}
	}
	else {
		std::cout << "directory not found, can't load textures" << std::endl;
	}
	return;
}

TextureManager* TextureManager::getInstance()
{
	if (!instance) {
		instance = new TextureManager();
		std::cout << "no instance found, creating instance";
	}
	return instance;
}

TextureManager* TextureManager::instance;

Texture TextureManager::getTexture(std::string texture)
{
	auto dir = getTextureDir();
	dir.append(texture);
	if ((*textures).find(dir) == (*textures).end() ) {
		return (*textures)[getTextureDir().append("walls\\invalid.png")];
	}
	return (*textures)[dir];
}

std::string TextureManager::getTextureDir()
{
	auto textureDir = std::string("assets\\textures\\");
	return textureDir;
}

TextureManager::TextureManager()
{
	textures = new std::map<std::string,Texture>();
}
