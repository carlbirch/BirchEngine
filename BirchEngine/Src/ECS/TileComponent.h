#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, std::string id)
	{
		texture = Game::assets->GetTexture(id);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = static_cast<int>(position.x - Game::cameraOffset.x);
		destRect.y = static_cast<int>(position.y - Game::cameraOffset.y);
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};