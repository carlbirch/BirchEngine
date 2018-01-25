#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"

class AssetManager
{
public:

	AssetManager(Manager* manager);
	~AssetManager();

	void CreateProjectile(Vector2D pos, int range, int speed, std::string texID);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

private:

	std::map<std::string, SDL_Texture*> textures;

	Manager* manager;
};