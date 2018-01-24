#pragma once
#include "ECS.h"
#include "Components.h"
#include <iostream>

class Projectile : public Component
{
public:
	Projectile(int r, int s) : range(r), speed(s)
	{
	}
	~Projectile()
	{}

	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		transform->velocity.x = static_cast<float>(speed);
	}

	void update() override
	{
		distance += speed;
		if (distance > range)
		{
			std::cout << "Max Range" << std::endl;
			entity->destroy();
		} 
		else if (transform->position.x > Game::cameraOffset.x + Game::cameraOffset.w)
		{
			std::cout << "Out Of Bounds" << std::endl;
			entity->destroy();
		}
	}

private:

	int speed;
	int range;
	int distance = 0;

};