#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "Thing.h"


class Bowl : public Thing
{
public:
	Bowl(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);

	void Update(float delta);
};