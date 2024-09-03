#pragma once

#include "map.h"
#include "Random.h"

class Controller {
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


	Map* map_array;
	int map_array_size;
	int* map_number;

	Prop* prop_array;
	int prop_array_size;

	Tile* tile_array;
	int tile_array_size;


	int controller_number;

	int goalX, goalY;
	Random* random_ptr;
	int current_direction;
	bool has_goal;
	int prop_search_id;
	int prop_type;
	bool holds_prop;
	bool wants_enter_door;



	void calculate_blocked_side(block_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length);
	void get_direction_blocked(block_direction_counter& counter, block_direction& direction, int length);
	void Update(float delta, const Uint8* keyState, int mode, Controller& p1);
	std::pair<int, int> direction_to_offset(int direction);
	void init_colision_map(std::vector<std::vector<bool>>& map);

public:

	Controller();

	void set_controller_number(int number);
	//void set_Stage(Stage* topography);
	void set_random_pointer(Random& random);

	void set_has_goal(bool value);	// this is for debug 
	void set_enter(bool value);
	void place_prop();		//set_prop
	void SetNewGoal(int x, int y);
	int GetDirection();
	bool is_prop_available_on_map();		//get available prop on map
	void make_goal();		// get new goal

	int get_controller_number();
	bool get_wants_enter_door();
	void set_wants_enter_door(bool value);
};