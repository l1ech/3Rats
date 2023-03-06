#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Body.h"
#include "Item.h"
#include "Tile.h"
#include "Random.h"

class Map
{
private:
	int item_id;
	int* item_on_map;
	double time;

	int width;
	int height;
	
	int rec_iter;

	std::vector<int> directions;
	std::vector<std::vector <std::vector<std::vector<int>>>>hyper_map;

	Item* item_array;
	int item_array_size;

	Tile* tile_array;
	int tile_array_size;

	std::pair<int, int> data[6][9];

	//types of generation
	void make_maze(bool item_generation);
	void make_garden(bool item_generations);

	//functions for maze generation
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction);
	void build_frame(std::vector<std::vector <int>>& map_data, std::pair<int , int >entrance, std::pair<int, int >exit, int wall, int space);
	void print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y);
	void trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);
	void set_corners(std::vector<std::vector <int>>& map_data);

	void save_data(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data);
	void set_items_to_map(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data, int height, int width);

	int get_tile(int x, int y);


public:
	Map();
	Map(const Map& b);
	Map(Tile arg[], int size, int w, int h, int type);
	~Map();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	//set up functions 
	void set_item_array(Item* item, int size);
	void set_tile_array(Tile* body, int size);	//make similar to item array
	void set_type(int type);
	void set_textures();

	//dev info
	void show_it();

	Tile* get_tile_array();
	int get_tile_array_size();

	Item* get_item_array();
	int get_item_array_size();

	void set_ptr(int* ptr);

};