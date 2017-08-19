#pragma once
#include <SDL.h>

class Collision
{
public:
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};
