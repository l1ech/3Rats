#include "Map.h"
#include <vector>


Map::Map(const Map& b)
{

}

Map::Map()
{

}


Map::Map(Body arg[], int size, int w, int h)
{
	width = w;
	height = h;

	body_array = arg;
	body_amount = size;

	int x_cord = 0;
	int y_cord = 0;

	for (int i = 0; i < body_amount; i++)
	{
		body_array[i].set_cords(x_cord, y_cord);
		body_array[i].set_texture("maze_wall.png");
		x_cord += 64;

		if (x_cord >= 576)
		{
			y_cord += 64;
			x_cord = 0;
		}
	}
	
}

Map::~Map()
{
}

int Map::get_tile(int x, int y)
{
	return y * width + x;
}

void Map::make_maze()
{
	//body_array[get_tile(0, 0)].set_cords(-100, -100);

	std::vector<std::vector <int>> maze_data(6,std::vector<int> (9));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			std::cout << "i: " << i << "|j: " << j << std::endl;
			maze_data[j][i] = 0;
		}
	}
	
	for (int i = 0; i < height; i++)
	{
		std::cout << i << "|";
		for (int j = 0; j < width; j++)
		{
			std::cout << maze_data[i][j];
		}
		std::cout << std::endl;
	}
	
	
}

void Map::Update(float delta)
{
	//std::cout << "update" << std::endl;
}

void Map::Draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < body_amount; i++)
	{
		body_array[i].Draw(renderTarget);
	}
}




