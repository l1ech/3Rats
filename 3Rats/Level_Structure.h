#pragma once

#include "Tile.h"
#include "Prop.h"
#include "Random.h"
#include "Door.h"



class Level_Structure
{
protected:

	Random* random_ptr;

	Prop* prop_array;	// implement to use instead of having maps do it
	int prop_array_size;

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

	void set_prop_array(Prop* prop, int prop_size);
	Prop* get_prop_array();
	int get_prop_size();

	void set_random_pointer(Random& random);
};