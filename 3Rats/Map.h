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
#include "Level_Structure.h"
#include "Door.h"

class Map : public Level_Structure
{
private:
	int map_id;

	int map_generation_try;

	Door door_array[3];

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
	void generate_maze(bool item_generation);
	void generate_garden(bool item_generations);
	void generate_cage(bool item_generation);

	// helper functions for generation
	void generate_door(int direction, int index, int type, bool active);
	void generate_doors(int entry_direction, int exit_direction, int type_generation, int end_x, int end_y);

	//functions for generation
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction);
	void build_frame(std::vector<std::vector <int>>& map_data, Door* door_array, int wall, int space);
	void print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y);
	void print_doors();
	void trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);
	//void set_corners(std::vector<std::vector <int>>& map_data);
	void save_data(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data);
	
	void set_items_to_map(std::vector<std::vector <int>>& map_data, std::vector<std::vector <int>>& item_data, int height, int width, int propability);

	int get_tile(int x, int y);

public:
	Map();
	~Map();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	void set_type(int type);
	void set_textures();
	void set_ptr(int* ptr);
	void set_map_id(int numer);
	void set_layout(std::string layout);


	int get_map_id();
	int get_hight();
	int get_width();
	Door get_door(int index);
};