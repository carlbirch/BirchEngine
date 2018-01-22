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
	ColliderComponent* collider;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		collider = &entity->getComponent<ColliderComponent>();
		transform->velocity.x = static_cast<float>(speed);
	}

	void update() override
	{
		distance += speed;
		std::cout << transform->position << std::endl;

		if(transform->position.x > Game::cameraOffset.x + Game::cameraOffset.w)
		{
			std::cout << "Destroyed at: " << transform->position << std::endl;
			entity->destroy();
		}
	}

private:

	int speed;
	int range;
	int distance = 0;

};