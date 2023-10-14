#pragma once	

#include <iostream>
#include <string>

#include "Body.h"
#include "Controller.h"

class Acteur : public Body, public Controller
{
private:
	int saturation;
	bool dead;

	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void check_door(Topography* topography, Map* map_array, int map_amount, Tile* tile_array, int length);
	void make_controller_move(controller_move move, block_direction direction, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Controller& front_rat);
	void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item);
	void hold_item_in_mouth(Item& item); 

	void update_arrays();


public:
	Acteur();
	~Acteur();

	void Update(float delta, const Uint8* keyState, int mode, Acteur& p1);
	void Draw(SDL_Renderer* renderTarget);

	void unstuck();	// change to set_pos(entrence);
	void set_cords_frames(int x, int y, int framesX, int framesY);
	bool intersectsWithBody(Body& b);		//get intersect
	void use_item();		// set_item_use
	void place_item();		//set_item


};

