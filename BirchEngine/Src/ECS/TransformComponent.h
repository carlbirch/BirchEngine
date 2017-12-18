#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	TransformComponent(float x, float y, int sc)
	{
		position.x = x;
		position.y = y;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		position.x += velocity.x * speed;  
		position.y += velocity.y * speed;
	}
};