#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../Game.h"
#include "../TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const char* path)
	{
		texture = TextureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;
		position.x = xpos;
		position.y = ypos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = position.x - Game::cameraOffset.x;
		destRect.y = position.y - Game::cameraOffset.y;
	}
	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};