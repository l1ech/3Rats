#include "Level.h"

Level::Level()
{
	number_items_on_map = 0;
	width = 5;
	height = 5;
}

void Level::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}

Map* Level::get_map_array()
{
	return map_array;
}

void Level::set_up()
{
	ptr = &number_items_on_map;

	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].set_ptr(ptr);
	}
}

void Level::update(float delta)
{
	//time += delta;

	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Update(delta);
	}
}

void Level::draw(SDL_Renderer* renderTarget)
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

void Level::set_renderer(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

Map* Level::get_map()
{
	return map_array;
}

int Level::get_map_size()
{
	return map_array_size;
}

void Level::make_maze()
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

	make_points(start_x, start_y, end_x, end_y);
	
	data.resize(height + 2);
	for (int i = 0; i < data.size(); i++) {
		data[i].resize(width + 2);
		for (int j = 0; j < data[i].size(); j++) {
			data[i][j] = std::make_pair(0, 0);
		}
	}

	map_data.resize(height);
	for (int i = 0; i < map_data.size(); i++) {
		map_data[i].resize(width);
		for (int j = 0; j < map_data[i].size(); j++) {
			map_data[i][j] = std::make_pair(0, 0);
		}
	}

	build_frame(data, connections[0].first, connections[0].second, 9, 1);

	std::cout << "data =============" << std::endl;
	print_vector(data, data[0].size(), data.size());


	std::cout << "hidden data =============" << std::endl;
	print_vector_hidden(data, data[0].size(), data.size());

	while (find_empty_space(connections[0].first.first, connections[0].first.second, data, data[start_x][start_y].first, 0) != 0) {}


	std::cout << "hidden data after fill =============" << std::endl;
	print_vector_hidden(data, data[0].size(), data.size());

	std::cout << "data =============" << std::endl;
	print_vector(data, data[0].size(), data.size());

	trim_boarder(data, map_data);

	std::cout << "map data =============" << std::endl;
	print_vector(map_data, map_data[0].size(), map_data.size());

	std::cout << "hidden map data =============" << std::endl;
	print_vector_hidden(map_data, map_data[0].size(), map_data.size());


	//save_data(map_data);
	
}

void Level::make_points(int a_x, int a_y, int b_x, int b_y)
{
	std::pair <int, int > point_a = { a_x, a_y };
	std::pair <int, int > point_b = { b_x, b_y };

	connections.push_back({ point_a, point_b });
}

void Level::build_frame(std::vector<std::vector<std::pair<int, int>>>& data, std::pair<int, int> entrance, std::pair<int, int> exit, int wall, int space)
{
	for (int h = 0; h < height + 2; h++)
	{
		for (int w = 0; w < width + 2; w++)
		{
			if (w == 0 || w == width + 1 || h == 0 || h == height + 1) 
				data[h][w].first = wall;
			else 
				data[h][w].first = space;

			data[h][w].second = 0;
		}
	}

	data[entrance.second][entrance.first].first = 2;
	data[exit.second][exit.first].first = 0;
}

int Level::find_empty_space(int x, int y, std::vector<std::vector<std::pair<int, int>>>& map, int& prev_direction, int iterator)
{
	iterator++;

	Random rand;

	int direction;

	// Set new location
	if (rand.flip_coin()) {  // Horizontal
		if (rand.flip_coin()) {
			direction = EAST;  // Right
			x++;
		}
		else {
			direction = WEST;  // Left
			x--;
		}
	}
	else {  // Vertical
		if (rand.flip_coin()) {
			direction = NORTH;  // Up
			y++;
		}
		else {
			direction = SOUTH;  // Down
			y--;
		}
	}

	// Try new location
	int point_value = map[y][x].first;

	if (point_value == EMPTY) {  // Empty field
		return point_value;
	}
	else if (point_value == WALL) {  // Wall
		map[y][x].first = direction;
		map[y][x].second = iterator;
		counter_maps = iterator;

		int vall = find_empty_space(x, y, map, direction, iterator);

		if (vall == EMPTY) {
			return vall;
		}
		else if (vall == WALL) {
			map[y][x].first = direction;
			map[y][x].second = iterator;
			counter_maps = iterator;
		}
		else {
			map[y][x].first = WALL;
			map[y][x].second = 0;
			return vall;
		}
	}
	else {  // Finish or path
		return point_value;
	}
}


void Level::trim_boarder(std::vector<std::vector<std::pair<int, int>>>& data, std::vector<std::vector<std::pair<int, int>>>& map_data)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			map_data[h][w].first = data[h + 1][w + 1].first;
			map_data[h][w].second = data[h + 1][w + 1].second;
		}
	}
}

void Level::print_vector(std::vector<std::vector<std::pair<int, int>>>& arg, int size_x, int size_y)
{
	std::cout << "vector: " << std::endl;

	for (int h = 0; h < size_y; h++)
	{
		for (int w = 0; w < size_x; w++)
		{
			std::cout << arg[h][w].first;

		}
		std::cout << std::endl;
	}
}

void Level::print_vector_hidden(std::vector<std::vector<std::pair<int, int>>>& arg, int size_x, int size_y)
{
	std::cout << "vector: " << std::endl;

	for (int h = 0; h < size_y; h++)
	{
		for (int w = 0; w < size_x; w++)
		{
			std::cout << arg[h][w].second;

		}
		std::cout << std::endl;
	}
}

int Level::get_layout(int num)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < height; w++)
		{
			int temp = map_data[h][w].second;
			if ( temp == num)
			{
				return map_data[h][w].first;
			}
		}
	}
}
