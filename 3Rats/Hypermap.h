#pragma once

#include "Map.h"
#include "Clock.h"

class Hypermap
{
private:
	SDL_Renderer* renderTarget;

	double time;

	Map* map_array;
	int map_array_size;

	Item* item_array;	// implement to use instead of having maps do it
	int item_array_size;

	Tile* tile_array;	// this 2
	int tile_array_size;

	int number_items_on_map;
	int* ptr;
public:
	Hypermap();

	void set_map_array(Map* map, int size);
	Map* get_map_array();
	int get_map_size();

	void set_tile_array(Tile* tile, int tile_size);
	Tile* get_tile_array();
	int get_tile_size();

	void set_item_array(Item* item, int item_size);
	Item* get_item_array();
	int get_item_size();

	void set_up();

	void update(float delta);
	void draw(SDL_Renderer* renderTarget);

	void set_renderer(SDL_Renderer* renderTarget);

	Map* get_map();

};