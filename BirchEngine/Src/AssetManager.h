#pragma once
#include <map>
#include <string>
#include "Vector2D.h"
#include "TextureManager.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"

class AssetManager
{
public:
	AssetManager(Manager* man);
	~AssetManager();

	void CreateProjectile(Vector2D pos, int rng, int sp, std::string id);

	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

private:
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, SDL_Texture*> textures;
	Manager* manager;
};