#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "Thing.h"

class Frame : public Thing
{
private:
public:
	Frame(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	void Update(float delta);
};