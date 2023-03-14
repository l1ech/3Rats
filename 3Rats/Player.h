#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Body.h"
#include "Item.h"
#include "Map.h"
#include "Tile.h"
#include "Hypermap.h"


class Player : public Body
{
private:
	Hypermap* hypermap;

	Random random;
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

	float moveSpeed;
	bool isActive;
	int direction_rat;

	int goalX, goalY;

	Item* item_array;
	int item_array_size;

	Tile* tile_array;
	int tile_array_size;

	int saturation;		// 0 - 100
						// ticksystem removing hunger

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

	struct player_move
	{
		bool up;
		bool down;
		bool left;
		bool right;
	};

	// for update fuction:
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void calculate_blocked_side(block_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length);
	void get_direction_blocked(block_direction_counter& counter, block_direction& direction, int length);
	void check_door(int& map_number,Map* map_array, int map_amount, Tile* tile_array, int length);
	void make_rat_position(int direction, int& rat_x, int& rat_y);
	int tick_food(int num);

	void make_player_move(player_move move, block_direction direction, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Player& front_rat);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item);

	void hold_item_in_mouth(Item& item);

public:


	Player();
	//Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	~Player();

	//void set_surface(SDL_Renderer* renderTarget, std::string name);
	void set_cords(int x, int y, int framesX, int framesY);
	void set_player_number(int number);
	void set_hypermap(Hypermap* hypermap);

	void Update(float delta, const Uint8* keyState, int mode, Player& p1, Map* map_array, int map_amount, int& map_number);
	void Draw(SDL_Renderer* renderTarget);  

	void SetNewGoal(int x, int y);

	int GetDirection();

	bool intersectsWithBody(Body& b);

	// needed to for the rats to find goals 
	bool is_item_available_on_map();
	void make_goal();

	// inputs from main to player object
	void use_item();
	void place_item();
	void set_has_goal(bool value);	// this is for debug 
	void set_enter(bool value);
};

