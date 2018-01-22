#pragma once
#include <map>
#include <string>

#include "TextureManager.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:
	std::map<std::string, SDL_Texture*> textures;


};