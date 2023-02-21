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

public:
	Map();
	Map(Body arg[], int size, int w, int h);
	Map(const Map& b);
	~Map();

	Body* body_array;


	void make_maze(int i, int j);
	void make_maze();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);
	int get_tile(int x, int y);

	void print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y);
	int rec_pos(int x, int y, std::vector<std::vector <int>>& arg);
	void trim_vector(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);
	void set_new_srand();

	bool flip_coin();







	//void set_surface(SDL_Renderer* renderTarget);
	//void set_cords(int x, int y);

	int body_amount;
};