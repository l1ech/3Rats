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
#include "Map_Structure.h"

class Map : public Map_Structure
{
private:

	int map_id;

	std::pair<int, int> entrence;
	std::pair<int, int> exit;
	std::pair<int, int> hole;

	int entry_direction;
	int exit_direction;

	int item_id;
	int* item_on_map;
	double time;

	int width;
	int height;
	
	int rec_iter;

	std::vector<int> directions;
	std::vector<std::vector <std::vector<std::vector<int>>>>hyper_map;

	std::pair<int, int> data[6][9];

	//types of generation
	void make_maze(bool item_generation);
	void make_garden(bool item_generations);
	void make_cage(bool item_generation);

	// helper functions for generation

	void make_doors_entry(int x, int y);
	void make_doors_exit(int x, int y);
	void make_doors_hole(int x, int y);

	void make_doors_entry(int direction);
	void make_doors_exit(int direction);


	//functions for maze generation
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction);
	void build_frame(std::vector<std::vector <int>>& map_data, std::pair<int , int >entrance, std::pair<int, int >exit, int wall, int space);
	void build_frame(std::vector<std::vector <int>>& map_data, int wall, int space);
	void print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y);
	void trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);
	void set_corners(std::vector<std::vector <int>>& map_data);

	void save_data(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data);
	void set_items_to_map(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data, int height, int width, int propability);

	int get_tile(int x, int y);


public:
	Map();
	Map(const Map& b);
	Map(Tile arg[], int size, int w, int h, int type);
	~Map();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	//set up functions 
	void set_type(int type);
	void set_textures();

	//dev info
	void show_it();

	void set_ptr(int* ptr);

	void set_map_id(int numer);
	int get_map_id();

	void set_layout(int num);

	std::pair <int, int> give_entry_door();
	std::pair <int, int> give_exit_door();
	std::pair <int, int> give_hole_door();

	Tile* get_tile_array();
	int get_tile_array_size();

	int get_hight();
	int get_width();

};