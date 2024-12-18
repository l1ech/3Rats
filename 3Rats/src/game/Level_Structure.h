#pragma once

#include"Tile.h"
#include"Item.h"
#include "../core/Random.h"

class Level_Structure
{
protected:

	Random* random_ptr;

	Item* item_array;	// implement to use instead of having maps do it
	int item_array_size;

	Tile* tile_array;	// this 2
	int tile_array_size;
	/*
	const std::string EMPTY = ".";
	const std::string WALL = "#";
	const std::string FINISH = "F";
	const std::string START = "S";

	const std::string NORTH = "N";
	const std::string EAST = "E";
	const std::string SOUTH = "S";
	const std::string WEST = "W";
	
	*/
	
	
public:
	void set_tile_array(Tile* tile, int tile_size);
	Tile* get_tile_array();
	int get_tile_size();

	void set_item_array(Item* item, int item_size);
	Item* get_item_array();
	int get_item_size();

	void set_random_pointer(Random& random);
};