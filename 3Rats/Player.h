#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Item.h"
#include "Body.h"
#include "Map.h"


class Player
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	SDL_Rect positionRect;


	float moveSpeed;
	float frameCounter, searchCounter, waitCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;

	int playerNumber;
	int direction;
	int goalX, goalY;
	bool search, found;
	bool bananPicked;
	bool wait;

	int height;

	bool block_up, block_down, block_left, block_right;

public:
	Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void Update(float delta, const Uint8* keyState, int mode, Player& p1, Item& i, int& bananAmount, Body arg[], int length, Map* map_array, int& map_number);
	void Draw(SDL_Renderer* renderTarget);  

	void SetNewGoal();
	void SetNewGoal(int x, int y);


	int GetOriginX();
	int GetOriginY();
	int GetRadius();
	int GetDirection();

	bool intersectsWithBody(Body& b);
};

