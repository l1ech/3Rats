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
	double time;

	int width;
	int height;
	
	int rec_iter;

	int body_amount;
	int item_amount;

	std::vector<int> directions;
	std::vector<std::vector <std::vector<std::vector<int>>>>hyper_map;

	Item* item_array;
	Tile* tile_array;

	std::pair<int, int> data[6][9];

	//types of generation
	void make_maze(bool item_generation);
	void make_garden();

	//functions for maze generation
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction);
	void build_frame(std::vector<std::vector <int>>& map_data, int start_x, int start_y, int end_x, int end_y);
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

};