#pragma once	

#include <iostream>
#include <string>

#include "../../../core/Constants.h"

#include "../../../core/Body.h"
#include "../../../input/Controller.h"

#include "../../factory/map_factory/Map.h"


#include "../item_manager/Item.h"
#include "../tile_manager/Tile.h"
#include "../door_manager/Door.h"

class Acteur : public Controller
{
protected:

	SDL_Scancode keys[4];

	float frameCounter, searchCounter;




	// holding item type 
	// should be done by the inventory not in the acteur!


	int item_hold_id;

	float waitCounter;
	bool wait;




	bool dead;

	int saturation;		// 0 - 100
	// ticksystem removing hunger

// for update fuction
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	//void check_door(Topography* topography, std::unique_ptr<Map>* map_array, int map_amount, Tile* tile_array, int length);
	//void make_acteur_move(controller_move move, block_direction direction, float delta);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat);
	//void follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item);
	void hold_item_in_mouth(Item& item);

public:
	//need body
	Acteur();

	void draw(SDL_Renderer* renderTarget) const;
	void Update(float delta, const Uint8* keyState, int mode, Acteur& p1);

	void set_cords_frames(int x, int y, int framesX, int framesY);

	//void teleport_to_entrence();	// change to set_pos(entrence);
	//bool intersectsWithBody(Body& b);		//get intersect

	//not
	~Acteur();
	void use_item();		// set_item_use

	
};
