#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>


class Thing {
public:
	//Thing(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	//~Thing();

	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

protected:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	SDL_Rect positionRect;


	float moveSpeed;
	float frameCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;
};