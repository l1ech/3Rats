#pragma once	

#include <iostream>
#include <string>

#include "../../../core/Body.h"
#include "../../../core/Constants.h"

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

	// Copy constructor
    Item(const Item& other);

    // Copy assignment operator
    Item& operator=(const Item& other);


	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget) const;

	bool get_on_map();
	void set_on_map(bool value);

	bool get_pick_up();
	void set_pick_up(bool value);


};