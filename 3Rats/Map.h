#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include "Body.h"

class Map
{
private:
	int x_size;
	int y_size;

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




	//void set_surface(SDL_Renderer* renderTarget);
	//void set_cords(int x, int y);

	int body_amount;
};