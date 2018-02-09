#pragma once

#include "ECS.h"
#include "../Vector2D.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component
{
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, SDL_Color& colour) : labelText(text), textColour(colour)
	{
		position.x = xpos;
		position.y = ypos;
		labelFont = font;
	}

	void SetLabel(std::string text, std::string fontId)
	{
		SDL_Surface* texSurf = TTF_RenderText_Blended(Game::assets->GetFont(fontId), text.c_str(), textColour);
		labelTexture = SDL_CreateTextureFromSurface(Game::renderer, texSurf);
		SDL_FreeSurface(texSurf);

		SDL_QueryTexture(labelTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void init() override
	{
		SetLabel(labelText, labelFont);
	}

	void update() override
	{

	}

	void draw() override
	{
		SDL_RenderCopy(Game::renderer, labelTexture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string labelText;
	std::string labelFont;
	SDL_Color textColour;
	SDL_Texture* labelTexture;
};