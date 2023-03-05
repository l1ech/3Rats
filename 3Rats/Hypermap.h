#pragma once

#include "Map.h"

class Hypermap
{
private:
	Map* map_array;
	int map_array_size;

	int number_items_on_map;
	int* ptr;
public:
	Hypermap();
	void set_map_array(Map* arg, int size);
	void set_up();

	void update(float delta);
	void draw(SDL_Renderer* renderTarget);

};