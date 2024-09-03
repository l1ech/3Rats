#pragma once	

#include <iostream>
#include <string>

#include "Body.h"
#include "Controller.h"
#include "Inventory.h"

class Acteur : public Body, public Controller, public Inventory
{
protected:

	int role;		// 0 = player, 1 = player_bot, 2 = npc

	SDL_Scancode keys[4];

	float frameCounter, searchCounter;

	// holding prop type 
	// should be done by the inventory not in the acteur!
	int prop_hold_id;

	float waitCounter;
	bool wait;

	float moveSpeed;
	bool is_moving;

	bool dead;

	int saturation;		// 0 - 100
	// ticksystem removing hunger

// for update fuction

	//map, tile, prop, topotgrapy
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void hold_prop_in_mouth(Prop& prop);

	//controller
	void make_acteur_move(controller_move move, block_direction direction, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Prop& prop);
	void follow(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat);

public:

	//need body
	Acteur();

	void Draw(SDL_Renderer* renderTarget);

	void update(float delta, int mode, Acteur& p1);
	void update(float delta, const Uint8* keyState);
	void update(float delta, Acteur& p1);


	void teleport_to_entrence();	// change to set_pos(entrence);
	bool intersectsWithBody(Body& b);		//get intersect
	void set_role(int r);
	void set_map_array(Map* map, int map_size);

	//not
	~Acteur();

	//inventory
	void use_prop();		// set_prop_use

	int pick_option();

	
};
