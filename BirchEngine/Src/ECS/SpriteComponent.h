#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:

	bool animated = false;
	int frames = 0;
	int speed = 100;
	int animIndex = 0;

	std::map<const char*, Animation> mAnimations;

	Animation currentAnimation;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}
	SpriteComponent(const char* path, bool mAnimated)
	{
		setTex(path);
		animated = true;
		
		Animation playerIdle = Animation(0, 3, 100);
		Animation playerWalk = Animation(1, 8, 100);

		mAnimations.emplace("Idle", playerIdle);
		mAnimations.emplace("Walk", playerWalk);

		Play("Idle");

		frames = currentAnimation.frames;
		speed = currentAnimation.speed;

	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;

	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}

	void Play(const char* anim_name)
	{
		currentAnimation = mAnimations[anim_name];
		frames = currentAnimation.frames;
		animIndex = currentAnimation.index;
		speed = currentAnimation.speed;
	}

};