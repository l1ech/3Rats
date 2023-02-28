#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Item.h"
#include "Body.h"
#include "Map.h"
#include "Tile.h"


class Player : public Body
{
private:
	int player_number;

	float moveSpeed;
	float waitCounter;
	bool isActive;

	//int playerNumber;
	int direction;
	int goalX, goalY;
	bool search, found;
	bool bananPicked;
	bool wait;

	bool block_up, block_down, block_left, block_right;
	int b_up, b_down, b_left, b_right;

public:
	Player();
	Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	void set_surface(SDL_Renderer* renderTarget, std::string name);
	void set_cords(int x, int y, int framesX, int framesY);
	void set_player_number(int number);

	void Update(float delta, const Uint8* keyState, int mode, Player& p1, Item& i, int& bananAmount, Tile arg[], int length, Map* map_array, int& map_number);
	void Draw(SDL_Renderer* renderTarget);  

	void SetNewGoal();
	void SetNewGoal(int x, int y);

	int GetDirection();

	bool intersectsWithBody(Body& b);
};

