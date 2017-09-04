#pragma once
#include <SDL.h>
#include <vector>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& a, const ColliderComponent& b);
};
