#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Body.h"

class Item : public Body
{
private:

	int ItemNumber;
	bool isExisting;


public:
	Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	Item();
	~Item();

	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	bool GetExistence();
	void SetExistence(bool value);
};