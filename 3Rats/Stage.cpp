#include "Stage.h"

Stage::Stage()
{
	number_items_on_map = 0;
	width = 5;
	height = 5;
	current_map_id = 0;
}

Map* Stage::get_map_array()
{
	return map_array;
}

void Stage::set_up()
{
	ptr = &number_items_on_map;

	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].set_ptr(ptr);
	}
}

int Stage::get_current_map_id()
{
	return current_map_id;
}

void Stage::set_current_map_id(int number)
{
	current_map_id = number;
}

void Stage::update(float delta)
{
	check_acteur_script();
	check_door();
}

void Stage::check_door()
{	
	Tile* tile_array = map_array[0].get_tile_array();
	int length = map_array[0].get_tile_size();

	// make it that all acteurs spawn at the new door
	// not at 0, 0 
	// new door could be anywhere

	int current_map_id = get_current_map_id();

	for (int i = 0; i < length; i++)
	{
		bool last_room = (current_map_id == map_array_size - 1);
		bool first_room = (current_map_id == 0);

		Acteur& player = player_array[0];

		bool wants_enter_door = player.get_wants_enter_door();
		int con_num = player.get_controller_number();

		if (!wants_enter_door) break;
		if (!(con_num == 0)) break;

		if (player.intersectsWithBody(tile_array[i]) && con_num == 0)
		{
			//wants_enter_door = false;
			player.set_wants_enter_door(false);
			if (tile_array[i].is_exit && !last_room)
			{
				current_map_id++;
				map_array[current_map_id].set_textures();
				Door entry = map_array[current_map_id].get_door(0);

				std::pair<int, int> value = player.get_crop_rect();

				player.set_pos_rect
				(
					entry.get_x() * 64 - value.first, 
					entry.get_y() * 64 - value.second
				);

				//position_rect.x = entry.get_x() * 64 - crop_rect.w;
				//position_rect.y = entry.get_y() * 64 - crop_rect.h;

				//std::cout << "acteur 1: " << this->controller_number << std::endl;
				//std::cout << "acteur 2: " << (this->controller_number)++ << std::endl;
				//std::cout << "acteur 3: " << ((this->crop_rect.w)++)++ << std::endl;

			}
			else if (tile_array[i].is_entrance && !first_room)
			{
				current_map_id--;
				map_array[current_map_id].set_textures();
				Door exit = map_array[current_map_id].get_door(1);

				std::pair<int, int> value = player.get_crop_rect();

				player.set_pos_rect
				(
					exit.get_x() * 64 - value.first,
					exit.get_y() * 64 - value.second
				);
			}
			else if (tile_array[i].is_hole && current_map_id != map_array_size - 1)
			{
				current_map_id++;
				map_array[current_map_id].set_textures();
				Door entry = map_array[current_map_id].get_door(0);

				std::pair<int, int> value = player.get_crop_rect();

				player.set_pos_rect
				(
					entry.get_x() * 64 - value.first,
					entry.get_y() * 64 - value.second
				);

				set_current_map_id(current_map_id);

				// for testing this is set to be linear map. which is wrong.
				// it has to be 3d so a hole would move the map in z direction 
				// also x and y should also have a directional influance on the map
			}
		}
	}
}

void Stage::check_acteur_script()
{
	Acteur& entity = entity_array[0];

	Acteur& player = player_array[0];

	if (entity.intersectsWithBody(player))
	{
		//int entity_option = entity.pick_option();	// options 1: fight, 2: flee, 3: parle, 4: wait
		//int player_option = player.pick_option();


		int entity_option = 3;
		int player_option = 3;

		if (entity_option == 3 && player_option == 3)
		{
			//talk
		}
	}
}

void Stage::draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Draw(renderTarget);
	}
}

void Stage::set_renderer(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

Map* Stage::get_map()
{
	return map_array;
}

int Stage::get_map_size()
{
	return map_array_size;
}

void Stage::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}

void Stage::set_player_array(Acteur* a, int size)
{
	player_array = a;
	player_array_size = size;
}

void Stage::set_entity_array(Acteur* a, int size)
{
	entity_array = a;
	entity_array_size = size;
}

void Stage::make_maze()
{
	std::cout << "generating topology..."<<std::endl;

	int start_x = 1;
	int start_y = 1;

	int end_x = width;
	int end_y = height;

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

void Stage::make_points(int a_x, int a_y, int b_x, int b_y)
{
	std::pair <int, int > point_a = { a_x, a_y };
	std::pair <int, int > point_b = { b_x, b_y };

	connections.push_back({ point_a, point_b });
}

void Stage::build_frame(std::vector<std::vector<std::pair<std::string, int>>>& data, std::pair<int, int> entrance, std::pair<int, int> exit)
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

std::string Stage::find_empty_space(int x, int y, std::vector<std::vector<std::pair<std::string, int>>>& map, std::string& prev_direction, int iterator)
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


void Stage::trim_boarder(std::vector<std::vector<std::pair<std::string, int>>>& data, std::vector<std::vector<std::pair<std::string, int>>>& map_data)
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

void Stage::print_vector(std::vector<std::vector<std::pair<std::string, int>>>& arg, int size_x, int size_y)
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

void Stage::print_vector_hidden(std::vector<std::vector<std::pair<std::string, int>>>& arg, int size_x, int size_y)
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

std::string Stage::get_layout(int num)
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
void Stage::set_random_pointer(Random& random) { random_ptr = &random; }

void Stage::teleport_to_entrence(Acteur* a)
{

	Map* map_ptr = get_map_array();

	a->set_cords(
		map_ptr[get_current_map_id()].get_door(0).get_x() * 64 - a->get_crop_rect().first,
		map_ptr[get_current_map_id()].get_door(0).get_y() * 64 - a->get_crop_rect().second
	);

}