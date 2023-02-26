#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <random>

#include <iostream>
#include <string>
#include <vector>


#include "Body.h"

class Map
{
private:
	int width;
	int height;
	int rec_iter;
	int body_amount;

	std::vector<int> directions;

public:
	Map();
	Map(Body arg[], int size, int w, int h);
	Map(const Map& b);
	~Map();

	Body* body_array;

	void make_maze();
	void make_garden();
	void show_it();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);
	int get_tile(int x, int y);

	//functions for make_maze()
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction);
	int get_direction(int prev_direction, int direction);
	void set_textures(std::vector<std::vector <int>>& map_data);
	void build_frame(std::vector<std::vector <int>>& map_data, int start_x, int start_y, int end_x, int end_y);
	void print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y);
	void trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);
	bool flip_coin();
	void set_corners(std::vector<std::vector <int>>& map_data);
};