#pragma once	

#include <iostream>
#include <string>

#include "handler/controller_handler/Controller.h"

#include "../core/Constants.h"

#include "../core/Body.h"

#include "Map.h"


#include "Item.h"
#include "Tile.h"
#include "Door.h"

class Acteur : public Controller
{
protected:

	SDL_Scancode keys[4];

	float frameCounter, searchCounter;

	int item_hold_id;

	float waitCounter;
	bool wait;

	bool dead;

	int saturation;		// 0 - 100
	// ticksystem removing hunger

// for update fuction
	std::vector<std::vector<bool>> get_blocked_array(Tile* tile_array, int length);
	void follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat);
	void hold_item_in_mouth(Item& item);

public:
	//need body
	Acteur();
    virtual ~Acteur() = default;

	void draw(SDL_Renderer* renderTarget) const;

    virtual void Update(float delta, const Uint8* keyState, int mode, Acteur& p1) = 0;
	
	void set_cords_frames(int x, int y, int framesX, int framesY);

	void use_item();		// set_item_use
};
