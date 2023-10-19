#include "Topography.h"

Topography::Topography()
{
	number_items_on_map = 0;
	width = 5;
	height = 5;
	current_map_id = 0;
}

void Topography::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}

Map* Topography::get_map_array()
{
	return map_array;
}

void Topography::set_up()
{
	ptr = &number_items_on_map;

	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].set_ptr(ptr);
	}
}

int Topography::get_current_map_id()
{
	return current_map_id;
}

void Topography::set_current_map_id(int number)
{
	current_map_id = number;
}

void Topography::update(float delta)
{
	//time += delta;

	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Update(delta);
	}
}

void Topography::draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Draw(renderTarget);
	}
	for (int i = 0; i < tile_array_size; i++)
	{
		tile_array[i].draw(renderTarget);
	}

	for (int i = 0; i < item_array_size; i++)
	{
		item_array[i].draw(renderTarget);
	}
}

void Topography::print_connections(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>)
{
	std::cout << "print points..." << std::endl;
}

void Topography::set_renderer(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

Map* Topography::get_map()
{
	return map_array;
}

int Topography::get_map_size()
{
	return map_array_size;
}

void Topography::make_maze()
{
	std::cout << "generating topology..."<<std::endl;

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

	print_connections(connections);
	
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

	build_frame(data, connections[0].first, connections[0].second);

	// change end char to be a bool value and if the generation was correct then 
	// return 1 else 0

	std::string end_char = "1";
	while (end_char != FINISH)
	{
		end_char = find_empty_space(connections[0].first.first, connections[0].first.second, data, data[start_x][start_y].first, 0);
	}

	
	std::cout << "___________ topology data - walkway__" << std::endl;
	print_vector(data, data[0].size(), data.size());

	std::cout << "___________ second layer  ___________" << std::endl;
	print_vector_hidden(data, data[0].size(), data.size());

	
	trim_boarder(data, map_data);

	std::cout << "___________ topology data ___________" << std::endl;
	print_vector(map_data, map_data[0].size(), map_data.size());

	std::cout << "___________ second layer  ___________" << std::endl;
	print_vector_hidden(map_data, map_data[0].size(), map_data.size());


	//save_data(map_data);
	
}

void Topography::make_points(int a_x, int a_y, int b_x, int b_y)
{
	std::pair <int, int > point_a = { a_x, a_y };
	std::pair <int, int > point_b = { b_x, b_y };

	connections.push_back({ point_a, point_b });
}

void Topography::build_frame(std::vector<std::vector<std::pair<std::string, int>>>& data, std::pair<int, int> entrance, std::pair<int, int> exit)
{
	for (int h = 0; h < height + 2; h++)
	{
		for (int w = 0; w < width + 2; w++)
		{
			if (w == 0 || w == width + 1 || h == 0 || h == height + 1) 
				data[h][w].first = WALL;
			else 
				data[h][w].first = EMPTY;

			data[h][w].second = 0;
		}
	}

	data[entrance.second][entrance.first].first = START;
	data[exit.second][exit.first].first = FINISH;
}

std::string Topography::find_empty_space(int x, int y, std::vector<std::vector<std::pair<std::string, int>>>& map, std::string& prev_direction, int iterator)
{
	iterator++;

	std::string direction;
	std::string prev_point_value = map[y][x].first;

	// Set new location
	// make this one structure a new function maybe???

	switch (random_ptr->roll_custom_dice(4))
	{
	case 1:
		direction = EAST;
		x++;
		break;

	case 2:
		direction = WEST;
		x--;
		break;

	case 3:
		direction = NORTH;
		y++;
		break;

	case 4:
		direction = SOUTH;
		y--;
		break;

	default:
		std::cout << "ERROR: Direction is wrong." << std::endl;
		break;
	}

	// Try new location
	std::string point_value = map[y][x].first;
	/*
	std::cout << "trying position... " << std::endl;
	std::cout << "[x: " << x << ", y: " << y << "] = "<< point_value << std::endl;
	*/
	
	if (point_value == EMPTY) {  // Empty field
		map[y][x].first = direction;
		map[y][x].second = iterator;
		counter_maps = iterator;

		std::string vall = find_empty_space(x, y, map, direction, iterator);

		if (vall == EMPTY) {
			map[y][x].first = direction;
			map[y][x].second = iterator;
			counter_maps = iterator;
		}
		else if (vall == FINISH)
		{
			return vall;
		}
		else
		{
			map[y][x].first = EMPTY;
			map[y][x].second = 0;
			return vall;
		}
	}
	else {  // Finish or path or Wall
		return point_value;
	}
}


void Topography::trim_boarder(std::vector<std::vector<std::pair<std::string, int>>>& data, std::vector<std::vector<std::pair<std::string, int>>>& map_data)
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

void Topography::print_vector(std::vector<std::vector<std::pair<std::string, int>>>& arg, int size_x, int size_y)
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

void Topography::print_vector_hidden(std::vector<std::vector<std::pair<std::string, int>>>& arg, int size_x, int size_y)
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

std::string Topography::get_layout(int num)
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
