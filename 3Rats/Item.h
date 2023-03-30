#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "Body.h"

class Item : public Body
{
private:


	bool is_on_map;
	bool is_picked_up;

	double weight;		// make it that this affacts 
						// how fast it can be carried arround
						// maybe: if two rats need 
						// to carry it together?


public:
	Item();
	~Item();

	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	bool get_on_map();
	void set_on_map(bool value);

	bool get_pick_up();
	void set_pick_up(bool value);


};