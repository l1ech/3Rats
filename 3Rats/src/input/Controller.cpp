#include "Controller.h"

void Controller::calculate_blocked_side(block_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (blocked_i[i][k])
			{
				if (k == 0) counter.right++;
				else if (k == 1) counter.left++;
				else if (k == 2) counter.down++;
				else if (k == 3) counter.up++;
				else {}
			}
			else
			{
				if (k == 0) counter.right--;
				else if (k == 1) counter.left--;
				else if (k == 2) counter.down--;
				else if (k == 3) counter.up--;
				else {}
			}
		}
	}
}

void Controller::get_direction_blocked(block_direction_counter& counter, block_direction& direction, int length)
{
	if (counter.right + length == 0) direction.right = false;
	else direction.right = true;

	if (counter.left + length == 0) direction.left = false;
	else direction.left = true;

	if (counter.down + length == 0) direction.down = false;
	else direction.down = true;

	if (counter.up + length == 0) direction.up = false;
	else direction.up = true;
}

void Controller::Update(float delta, const Uint8* keyState, int mode, Controller& p1)
{

}

std::pair<int, int> Controller::direction_to_offset(int direction)
{
	std::pair<int, int> pos = { 0, 0 };

	switch (direction) {
	case 0:
		pos.second -= 55;
		break;
	case 1:
		pos.second += 55;
		break;
	case 2:
		pos.first -= 55;
		break;
	case 3:
		pos.first += 55;
		break;
	default:
		break;
	}

	return pos;
}
void Controller::init_colision_map(std::vector<std::vector<bool>>& map)
{
	// initialize the outer vector with tile_array_size rows
	map.resize(tile_array_size);

	// initialize each inner vector with 4 columns and set all values to false
	for (int i = 0; i < tile_array_size; ++i) {
		map[i].resize(4, false);
	}

}
void Controller::set_controller_number(int number)
{
	controller_number = number;
}

void Controller::set_Topography(Topography* h)
{
	topography = h;
}

void Controller::set_random_pointer(Random& random)
{
	random_ptr = &random;
}


void Controller::SetNewGoal(int x, int y) { goalX = x; goalY = y; }

int Controller::GetDirection() { return current_direction; }

bool Controller::is_item_available_on_map()
{
	bool available = false;

	for (int i = 0; i < item_array_size; i++)
	{
		if (!item_array[i].get_pick_up())
		{
			if (item_array[i].get_on_map())
			{
				available = true;
			}
		}
	}
	return available;
}

void Controller::make_goal()
{
	int random_item_number = 0;

	while (!has_goal)
	{
		if (item_array[random_item_number].get_on_map() && random_ptr->flip_coin())
		{
			has_goal = true;

			SetNewGoal
			(
				item_array[random_item_number].get_origin_x(),
				item_array[random_item_number].get_origin_y()
			);

			item_search_id = random_item_number;

			std::cout << "p: " << controller_number << "gx: " << goalX << " gy: " << goalY << std::endl;

		}

		random_item_number++;

		if (random_item_number == item_array_size - 1) random_item_number = 0;
	}
}

void Controller::place_item()
{
	if (item_type == 0)
	{

	}
	else if (item_type == 1)
	{
		holds_item = false;
		std::cout << "placed!" << std::endl;
		item_type = 0;

	}
}

void Controller::set_has_goal(bool value) { has_goal = value; }

void Controller::set_enter(bool value) { wants_enter_door = value; }

void Controller::check_door(Topography* topography, std::unique_ptr<Map>* map_array, int map_amount, Tile* tile_array, int length)
{
	// make it that all acteurs spawn at the new door
	// not at 0, 0 
	// new door could be anywhere

	int current_map_id = topography->get_current_map_id();

	for (int i = 0; i < length; i++)
	{
		bool last_room = (current_map_id == map_amount - 1);
		bool first_room = (current_map_id == 0);

		if (!wants_enter_door) break;
		if (!(controller_number == 0)) break;

		if (intersectsWithBody(tile_array[i]) && controller_number == 0)
		{
			wants_enter_door = false;
			if (tile_array[i].is_exit && !last_room)
			{
				current_map_id++;
				topography->set_current_map_id(current_map_id);
				//map_array[current_map_id]->set_textures(); 
				// this used to be the heartessence of map generation
				Door entry = map_array[current_map_id]->get_door(0);

				position_rect.x = entry.get_x() * 64 - crop_rect.w;
				position_rect.y = entry.get_y() * 64 - crop_rect.h;

				//std::cout << "acteur 1: " << this->controller_number << std::endl;
				//std::cout << "acteur 2: " << (this->controller_number)++ << std::endl;
				//std::cout << "acteur 3: " << ((this->crop_rect.w)++)++ << std::endl;

			}
			else if (tile_array[i].is_entrance && !first_room)
			{
				current_map_id--;
				topography->set_current_map_id(current_map_id);
				//map_array[current_map_id]->set_textures();
				Door exit = map_array[current_map_id]->get_door(1);

				position_rect.x = exit.get_x() * 64 - crop_rect.w;
				position_rect.y = exit.get_y() * 64 - crop_rect.h;
			}
			else if (tile_array[i].is_hole && current_map_id != map_amount - 1)
			{
				current_map_id++;
				topography->set_current_map_id(current_map_id);
				//map_array[current_map_id]->set_textures();
				Door entry = map_array[current_map_id]->get_door(0);

				position_rect.x = entry.get_x() * 64 - crop_rect.w;
				position_rect.y = entry.get_y() * 64 - crop_rect.h;

				// for testing this is set to be linear map. which is wrong.
				// it has to be 3d so a hole would move the map in z direction 
				// also x and y should also have a directional influance on the map
			}
		}
	}
}

void Controller::make_acteur_move(controller_move move, block_direction direction, float delta)
{
	if (move.up && !direction.up)	//up
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (move.down && !direction.down)			//down
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (move.left && !direction.left)			//left
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (move.right && !direction.right)			//right
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else
	{
		is_moving = false;
	}
}


void Controller::follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Item& item)
{
	if (rat_y > goal_y && !direction.up)
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (rat_y < goal_y && !direction.down)
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (rat_x > goal_x && !direction.left)
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (rat_x < goal_x && !direction.right)
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else if (rat_x == goal_x && rat_y == goal_y && !item.get_pick_up())
	{
		std::cout << "[Controller<"<< index <<">]: found!" << " p: " << controller_number << "item number: " << item_search_id << std::endl;;

		//item_hold_id = item_search_id;
		holds_item = true;
		item.set_pick_up(true);
		has_goal = false;

		item_type = 1;

	}
	else if (rat_x == goal_x && rat_y == goal_y && item.get_pick_up())
	{
		std::cout << "[Controller<"<< index <<">]: did not found!" << " p: " << controller_number << "item number: " << item_search_id << std::endl;;
		has_goal = false;
	}
}

void Controller::teleport_to_entrence()
{
	std::unique_ptr<Map>* map_ptr = topography->get_map_array();

	set_cords(
		map_ptr[topography->get_current_map_id()]->get_door(0).get_x() * 64 - crop_rect.w,
		map_ptr[topography->get_current_map_id()]->get_door(0).get_y() * 64 - crop_rect.h
	);
}

bool Controller::intersectsWithBody(Body& b)
{
	if (sqrt(pow(get_origin_x() - b.get_origin_x(), 2) + pow(get_origin_y() - b.get_origin_y(), 2)) >= radius + b.get_radius())
	{
		return false;
	}
	return true;
}