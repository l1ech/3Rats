#pragma once

#include"Tile.h"
#include"Item.h"

class Level_Structure
{
protected:
	Item* item_array;	// implement to use instead of having maps do it
	int item_array_size;

	Tile* tile_array;	// this 2
	int tile_array_size;
public:
	void set_tile_array(Tile* tile, int tile_size);
	Tile* get_tile_array();
	int get_tile_size();

	void set_item_array(Item* item, int item_size);
	Item* get_item_array();
	int get_item_size();


};