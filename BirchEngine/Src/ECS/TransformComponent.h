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

	bool blocked = false;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.Zero();
	}

	TransformComponent(float x, float y, int h, int w, int sc)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override
	{
		velocity.Zero();
	}
	void update() override
	{
		position.x += static_cast<int>(velocity.x * speed);
		position.y += static_cast<int>(velocity.y * speed);
	}

};