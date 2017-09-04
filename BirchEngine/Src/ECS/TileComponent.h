#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	
	TransformComponent *transform;
	SpriteComponent *sprite;

	int tileID;
	SDL_Rect tileSize;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int h, int w, int id)
	{
		tileSize.x = x;
		tileSize.y = y;
		tileSize.h = h;
		tileSize.w = w;
		tileID = id;
		switch (tileID)
		{
		case 0:
			path = "assets/dirt.png";
		break;
		case 1:
			path = "assets/grass.png";
		break;
		case 2:
			path = "assets/water.png";
		break;
		default:
			break;
		}
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileSize.x, (float)tileSize.y, tileSize.h, tileSize.w, 1);
		
		transform = &entity->getComponent<TransformComponent>();
		
		transform->position.x = static_cast<float>(tileSize.x);
		transform->position.y = static_cast<float>(tileSize.y);
		transform->width = tileSize.w;
		transform->height = tileSize.h;
		
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}

};