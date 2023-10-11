#pragma once	

#include <iostream>
#include <string>
#include <tuple>

#include "Body.h"
#include "Item.h"
#include "Map.h"
#include "Tile.h"
#include "Topography.h"
#include "Door.h"
#include "Move_controller.h"

class Player : public Body, public Move_controller
{
private:

	SDL_Scancode keys[4];

	float frameCounter, searchCounter;

	Topography* topography;

	int player_number;


	// holding item type 
	// should be done by the inventory not in the player!
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

	struct player_move
	{
		bool up;
		bool down;
		bool left;
		bool right;
	};


	float moveSpeed;
	bool is_moving;
	int current_direction;

	bool dead;

	Random* random_ptr;


	int saturation;		// 0 - 100
						// ticksystem removing hunger

	// for update fuction
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	int check_door(Topography* topography,Map* map_array, int map_amount, Tile* tile_array, int length);
	bool handle_exit(int current_map);
	bool handle_entrance(int current_map);
	bool handle_hole(int current_map);
	
	std::pair<int, int> direction_to_offset(int direction);
	int tick_food(int num);
	void init_colision_map(std::vector<std::vector<bool>>& map);

	void make_player_move(player_move move, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, float delta, Player& front_rat);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, float delta, Item& item);

	void hold_item_in_mouth(Item& item);

	void food_tick();

public:
	Player();
	~Player();

	void Update(float delta, const Uint8* keyState, int mode, Player& p1);
	void Draw(SDL_Renderer* renderTarget);

	void set_cords_frames(int x, int y, int framesX, int framesY);
	void set_player_number(int number);
	void set_Topography(Topography* topography);
	void set_random_pointer(Random& random);
	void set_has_goal(bool value);	// this is for debug 
	void set_enter(bool value);
	void place_item();		//set_item
	void teleport_to_entrence();	// change to set_pos(entrence);
	void SetNewGoal(int x, int y);
	void use_item();		// set_item_use

	int GetDirection();
	bool intersectsWithBody(Body& b);		//get intersect
	bool is_item_available_on_map();		//get available item on map
	void make_goal();		// get new goal

};

