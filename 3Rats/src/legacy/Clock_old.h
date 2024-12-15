#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

#include "Thing.h"

class Clock : public Thing
{
private:
	float clockCounter;

	int min, hou;
public:
	Clock(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	void Update(float delta, float wait, bool zen,int *time);
};