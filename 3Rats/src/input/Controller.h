#pragma once
#include <SDL.h>

#include <vector>

#include "../game/stage/Topography.h"
#include "../core/Random.h"

class Controller : public Body
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


	std::unique_ptr<Map>* map_array;
	int map_array_size;
	int* map_number;

	Item* item_array;
	int item_array_size;

	Tile* tile_array;
	int tile_array_size;

	Topography* topography;

	int controller_number;

	int goalX, goalY;
	Random* random_ptr;
	int current_direction;
	bool has_goal;
	int item_search_id;
	int item_type;
	bool holds_item;
	bool wants_enter_door;



	void calculate_blocked_side(block_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length);
	void get_direction_blocked(block_direction_counter& counter, block_direction& direction, int length);
	void Update(float delta, const Uint8* keyState, int mode, Controller& p1);
	std::pair<int, int> direction_to_offset(int direction);
	void init_colision_map(std::vector<std::vector<bool>>& map);

public:
	bool intersectsWithBody(Body& b);
	void check_door(Topography* topography, std::unique_ptr<Map>* map_array, int map_amount, Tile* tile_array, int length);
	void make_acteur_move(controller_move move, block_direction direction, float delta);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item);

	float moveSpeed;

	bool is_moving;





	void set_controller_number(int number);
	void set_Topography(Topography* topography);
	void set_random_pointer(Random& random);

	void set_has_goal(bool value);	// this is for debug 
	void set_enter(bool value);
	void place_item();		//set_item
	void SetNewGoal(int x, int y);
	int GetDirection();
	bool is_item_available_on_map();		//get available item on map
	void make_goal();		// get new goal


	void teleport_to_entrence();	// change to set_pos(entrence);

};