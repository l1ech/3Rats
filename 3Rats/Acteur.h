#pragma once	

#include <iostream>
#include <string>

#include "Body.h"
#include "Item.h"
#include "Map.h"
#include "Tile.h"
#include "Topography.h"
#include "Door.h"
#include "Controller.h"

class Acteur : public Body, public Controller
{
protected:

	SDL_Scancode keys[4];

	float frameCounter, searchCounter;

	Topography* topography;

	int acteur_number;


	// holding item type 
	// should be done by the inventory not in the acteur!
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



	float moveSpeed;
	bool is_moving;
	int current_direction;

	bool dead;

	Random* random_ptr;
	int saturation;		// 0 - 100
	// ticksystem removing hunger

// for update fuction
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void check_door(Topography* topography, Map* map_array, int map_amount, Tile* tile_array, int length);
	std::pair<int, int> direction_to_offset(int direction);
	int tick_food(int num);
	void init_colision_map(std::vector<std::vector<bool>>& map);

	void make_acteur_move(acteur_move move, block_direction direction, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item);

	void hold_item_in_mouth(Item& item);

	void food_tick();

public:
	Acteur();
	~Acteur();

	void Update(float delta, const Uint8* keyState, int mode, Acteur& p1);
	void Draw(SDL_Renderer* renderTarget);

	void set_cords_frames(int x, int y, int framesX, int framesY);
	void set_acteur_number(int number);
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
