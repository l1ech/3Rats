#pragma once	

#include <iostream>
#include <string>

#include "Body.h"
#include "Item.h"
#include "Map.h"
#include "Tile.h"
#include "Topography.h"
#include "Door.h"
#include "Mop.h"
#include "Controller.h"

class Controller
{
protected:

	struct block_direction_counter {
		int right;
		int left;
		int up;
		int down;
	};

	struct block_direction {
		bool right;
		bool left;
		bool up;
		bool down;
	};

	struct controller_move
	{
		bool up;
		bool down;
		bool left;
		bool right;
	};


	float moveSpeed;
	bool is_moving;
	int current_direction;


	Random* random_ptr;


	SDL_Scancode keys[4];

	float frameCounter, searchCounter;

	Topography* topography;

	int controller_number;


	// holding item type 
	// should be done by the inventory not in the controller!
	int item_type;

	bool wants_enter_door;

	int item_hold_id;
	int item_search_id;
	bool holds_item;
	bool has_goal;

	float waitCounter;
	bool wait;

	int goalX, goalY;

	Map* map_array;
	int map_array_size;
	int* map_number;

	Item* item_array;
	int item_array_size;

	Tile* tile_array;
	int tile_array_size;


	void calculate_blocked_side(block_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length);
	void get_direction_blocked(block_direction_counter& counter, block_direction& direction, int length);
	std::pair<int, int> direction_to_offset(int direction);
	void init_colision_map(std::vector<std::vector<bool>>& map);

public:
	Controller();
	~Controller();

	//Controller
	void set_controller_number(int number);

	//AI
	void set_has_goal(bool value);	// this is for debug 
	void SetNewGoal(int x, int y);

	
	//PLAYER
	void set_enter(bool value);
	int GetDirection();
	bool is_item_available_on_map();		//get available item on map
	void make_goal();						// get new goal

	// does this need to be here?
	void set_Topography(Topography* topography);
	void set_random_pointer(Random& random);
};

