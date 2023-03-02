#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Body.h"
#include "Item.h"
#include "Map.h"
#include "Tile.h"


class Player : public Body
{
private:
	int player_number;

	float moveSpeed;
	float waitCounter;
	bool isActive;

	int direction_rat;
	int goalX, goalY;
	bool search, found;
	bool bananPicked;
	bool wait;

	bool block_up, block_down, block_left, block_right;

	struct break_direction_counter {
		int right;
		int left;
		int up;
		int down;
	};

	struct break_direction {
		bool right;
		bool left;
		bool up;
		bool down;
	};

	// for update fuction:
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void calculate_blocked_side(break_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length);
	void get_direction_blocked(break_direction_counter& counter, break_direction& direction, int length);

public:


	Player();
	Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	//void set_surface(SDL_Renderer* renderTarget, std::string name);
	void set_cords(int x, int y, int framesX, int framesY);
	void set_player_number(int number);

	void Update(float delta, const Uint8* keyState, int mode, Player& p1, Item& i, int& bananAmount, Tile arg[], int length, Map* map_array, int& map_number);
	void Draw(SDL_Renderer* renderTarget);  

	void SetNewGoal();
	void SetNewGoal(int x, int y);

	int GetDirection();

	bool intersectsWithBody(Body& b);
};

