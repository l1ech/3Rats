#include "Hypermap.h"

Hypermap::Hypermap()
{
	number_items_on_map = 0;
	width = 5;
	height = 5;
}

void Hypermap::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}

Map* Hypermap::get_map_array()
{
	return map_array;
}

void Hypermap::set_tile_array(Tile* tile, int tile_size)
{

	tile_array = tile;
	tile_array_size = tile_size;
}

Tile* Hypermap::get_tile_array()
{
	return tile_array;
}

int Hypermap::get_tile_size()
{
	return tile_array_size;
}

void Hypermap::set_item_array(Item* item, int item_size)
{
	item_array = item;
	item_array_size = item_size;
}

Item* Hypermap::get_item_array()
{
	return item_array;
}

int Hypermap::get_item_size()
{
	return item_array_size;
}

void Hypermap::set_up()
{
	ptr = &number_items_on_map;

	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].set_ptr(ptr);
	}
}

void Hypermap::update(float delta)
{
	//time += delta;

	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Update(delta);
	}
}

void Hypermap::draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Draw(renderTarget);
	}
	for (int i = 0; i < tile_array_size; i++)
	{
		tile_array[i].Draw(renderTarget);
	}

	for (int i = 0; i < item_array_size; i++)
	{
		item_array[i].Draw(renderTarget);
	}
}

void Hypermap::set_renderer(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

Map* Hypermap::get_map()
{
	return map_array;
}

int Hypermap::get_map_size()
{
	return map_array_size;
}

void Hypermap::make_maze()
{
	int start_x = 1;
	int start_y = 1;

	int end_x = width;
	int end_y = height;

	/*
	make_doors_entry(3);
	make_doors_exit(1);
	make_doors_hole(-100, -100);
	*/

	make_points(1, 1, 5, 5);
	
	std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));
	std::vector<std::vector <int>> map_data(height, std::vector<int>(width));

	build_frame(data, connections[0].first, connections[0].second, 9, 1);

	std::cout << "data =============" << std::endl;
	print_vector(data, data[0].size(), data.size());

	while (rec_pos(connections[0].first.first, connections[0].first.second, data, data[start_x][start_y]) != 0) {}


	std::cout << "=============" << std::endl;
	print_vector(map_data, map_data[0].size(), map_data.size());

	trim_boarder(data, map_data);

	std::cout << "=============" << std::endl;
	print_vector(map_data, map_data[0].size(), map_data.size());

	//save_data(map_data);
	
}

void Hypermap::make_points(int a_x, int a_y, int b_x, int b_y)
{
	std::pair <int, int > point_a = { a_x, a_y };
	std::pair <int, int > point_b = { b_x, b_y };

	connections.push_back({ point_a, point_b });
}

void Hypermap::build_frame(std::vector<std::vector<int>>& data, std::pair<int, int> entrance, std::pair<int, int> exit, int wall, int space)
{
	for (int h = 0; h < height + 2; h++)
	{
		for (int w = 0; w < width + 2; w++)
		{
			if (w == 0 || w == width + 1 || h == 0 || h == height + 1) data[h][w] = wall;
			else data[h][w] = space;

		}
	}

	data[entrance.second][entrance.first] = 2;
	data[exit.second][exit.first] = 0;
}

int Hypermap::rec_pos(int x, int y, std::vector<std::vector<int>>& arg, int& prev_direction)
{
	Random rand;

	int direction;

	//print_vector(arg, width + 2, height + 2);

	//================= set new location
	if (rand.flip_coin())
	{//horizontal
		if (rand.flip_coin())
		{
			direction = 3;
			x++;
		}//right
		else
		{
			direction = 4;
			x--;
		}//left
	}
	else
	{//vertical
		if (rand.flip_coin())
		{
			direction = 5;
			y++;
		}//up
		else
		{
			direction = 6;
			y--;
		}//down
	}
	//================= try new location

	int point_value = arg[y][x];

	if (point_value == 0)                         // finish or path
	{
		return point_value;
	}
	else if (point_value == 1)                    // empty field == wall
	{
		arg[y][x] = direction;

		int vall = rec_pos(x, y, arg, direction);

		if (vall == 0)
		{
			return vall;
		}
		else if (vall == 1)
		{

			arg[y][x] = direction;
		}
		else
		{
			arg[y][x] = 1;
			return vall;
		}
	}
	else
	{
		return point_value;
	}
}

void Hypermap::trim_boarder(std::vector<std::vector<int>>& data, std::vector<std::vector<int>>& map_data)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			map_data[h][w] = data[h + 1][w + 1];
		}
	}
}

void Hypermap::print_vector(std::vector<std::vector<int>>& arg, int size_x, int size_y)
{
	std::cout << "vector: " << std::endl;

	for (int h = 0; h < size_y; h++)
	{
		for (int w = 0; w < size_x; w++)
		{
			std::cout << arg[h][w];

		}
		std::cout << std::endl;
	}
}
