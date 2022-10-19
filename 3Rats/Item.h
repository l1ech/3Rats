#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

class Item
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	SDL_Rect positionRect;


	float moveSpeed;
	float frameCounter, searchCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;

	int ItemNumber;
	bool isExisting;

public:
	Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Item();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
	bool GetExistence();
	void SetExistence(bool value);

	void SetX(int x);
	void SetY(int y);
};