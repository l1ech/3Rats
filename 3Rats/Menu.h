#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Thing.h"

class Menu : public Thing
{
public:
	Menu(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);

	void SetTexture(SDL_Renderer* renderTarget, std::string filePath);
	SDL_Texture* LoadTexture( SDL_Renderer* renderTarget, std::string filePath);

	void Update(float delta, int hunger);
	void Draw(SDL_Renderer* renderTarget);
};