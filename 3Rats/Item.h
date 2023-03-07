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


public:
	Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y);
	Item(Item& other);
	Item();
	~Item();

	//Item& operator=(Item& other);

	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	bool get_on_map();
	void set_on_map(bool value);

	bool get_pick_up();
	void set_pick_up(bool value);


};