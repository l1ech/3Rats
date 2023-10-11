#include "Player.h"

std::vector<std::vector<bool>> Player::get_blocked_array(Tile* tile_array, int length)
{

	// make vector for tile and what direction it blocks
	std::vector<std::vector<bool>> blocked_i(length, std::vector<bool>(4));

	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			blocked_i[i][k] = false;
		}
	}

	// struckt with the directions to be blocked

	struct direction {
		bool right;
		bool left;
		bool up;
		bool down;
	};

	direction block = { false, false, false, false };

	for (int i = 0; i < length; i++)
	{
		if (intersectsWithBody(tile_array[i]))
		{
			if (tile_array[i].get_hight() == 1)
			{

				int delta_x = tile_array[i].get_origin_x() - position_rect.x;
				int delta_y = tile_array[i].get_origin_y() - position_rect.y;

				if (delta_x > 0) block.right = true;
				else if (delta_x < 0) block.left = true;

				if (delta_y > 0) block.down = true;
				else if (delta_y < 0) block.up = true;

				blocked_i[i][0] = block.right;
				blocked_i[i][1] = block.left;
				blocked_i[i][2] = block.down;
				blocked_i[i][3] = block.up;
			}
			else if (tile_array[i].get_hight() == 0)
			{
				block.right = false;
				block.left = false;
				block.down = false;
				block.up = false;
			}
		}
	}
	return blocked_i;
}

bool Player::handle_exit(int current_map_id)
{
	// Handle exit tile logic
	current_map_id++;
	topography->set_current_map_id(current_map_id);
	map_array[current_map_id].set_textures();
	Door entry = map_array[current_map_id].get_door(0);

	position_rect.x = entry.get_x() * 64 - crop_rect.w;
	position_rect.y = entry.get_y() * 64 - crop_rect.h;

	return true;
}

bool Player::handle_entrance(int current_map_id)
{
	// Handle entrance tile logic
	current_map_id--;
	topography->set_current_map_id(current_map_id);
	map_array[current_map_id].set_textures();
	Door exit = map_array[current_map_id].get_door(1);

	position_rect.x = exit.get_x() * 64 - crop_rect.w;
	position_rect.y = exit.get_y() * 64 - crop_rect.h;

	return true;
}

bool Player::handle_hole(int current_map_id)
{
	// Handle hole tile logic
	current_map_id++;
	topography->set_current_map_id(current_map_id);
	map_array[current_map_id].set_textures();
	Door entry = map_array[current_map_id].get_door(0);

	position_rect.x = entry.get_x() * 64 - crop_rect.w;
	position_rect.y = entry.get_y() * 64 - crop_rect.h;

	return true;
}

int Player::check_door(Topography* topography, Map* map_array, int map_amount, Tile* tile_array, int length)
{
	int current_map_id = topography->get_current_map_id();
	bool last_room = (current_map_id == map_array_size - 1);
	bool first_room = (current_map_id == 0);

	for (int i = 0; i < length; i++)
	{
		if (!intersectsWithBody(tile_array[i]))
		{
			continue;
		}

		wants_enter_door = false;

		if (tile_array[i].is_exit && !last_room)
		{
			if (handle_exit(current_map_id)) return 1;
		}
		else if (tile_array[i].is_entrance && !first_room)
		{
			if (handle_entrance(current_map_id)) return 2;
		}
		else if (tile_array[i].is_hole && current_map_id != map_amount - 1)
		{
			if (handle_hole(current_map_id)) return 3;
		}
	}

	return 0;
}


std::pair<int, int> Player::direction_to_offset(int direction)
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

int Player::tick_food(int num)
{
	//random.roll_custom_dice(10);	//10% 1/10 ?

	if (random_ptr->roll_custom_dice(num) == 1) return 1;
	else return 0;
}


void Player::init_colision_map(std::vector<std::vector<bool>>& map)
{
	// initialize the outer vector with tile_array_size rows
	map.resize(tile_array_size);

	// initialize each inner vector with 4 columns and set all values to false
	for (int i = 0; i < tile_array_size; ++i) {
		map[i].resize(4, false);
	}

}

void Player::make_player_move(player_move move, float delta)
{
	if (move.up)	//up
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (move.down)			//down
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (move.left)			//left
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (move.right)			//right
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

void Player::follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, float delta, Player& front_rat)
{
	if (rat_y > front_rat_y)
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (rat_y < front_rat_y)
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (rat_x > front_rat_x)
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (rat_x < front_rat_x)
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else
	{
		current_direction = front_rat.GetDirection();
	}

	if (current_direction == 0) crop_rect.y = frame_height * 3;
	if (current_direction == 1) crop_rect.y = 0;
	if (current_direction == 2) crop_rect.y = frame_height;
	if (current_direction == 3) crop_rect.y = frame_height * 2;
}

void Player::follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, float delta, Item& item)
{
	if (rat_y > goal_y)
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (rat_y < goal_y)
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (rat_x > goal_x)
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (rat_x < goal_x)
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else if (rat_x == goal_x && rat_y == goal_y&& !item.get_pick_up())
	{
		std::cout << "found!" << " p: " << player_number << "item number: " << item_search_id << std::endl;;

		item_hold_id = item_search_id;
		holds_item = true;
		item.set_pick_up(true);
		has_goal = false;

		item_type = 1;
		
	}
	else if (rat_x == goal_x && rat_y == goal_y && item.get_pick_up())
	{
		std::cout << "did not found!" << " p: " << player_number << "item number: " << item_search_id << std::endl;;
		has_goal = false;
	}
}

void Player::hold_item_in_mouth(Item& item)
{
	// add he offsets to make more sense. just for example i did it fo 14
	int offset = 14;

	if (current_direction == 0)
	{
		item.set_cords(get_origin_x() - 24, get_origin_y() - 32 - offset);
	}
	else if (current_direction == 1)
	{
		item.set_cords(get_origin_x() - 24, get_origin_y() - 32 + offset);
	}
	else if (current_direction == 2)
	{
		item.set_cords(get_origin_x() - 24 - offset, get_origin_y() - 32);
	}
	else if (current_direction == 3)
	{
		item.set_cords(get_origin_x() - 24 + offset, get_origin_y() - 32);
	}
}

void Player::food_tick()
{
	if (tick_food(100)) saturation--;

	if (saturation == 20) std::cout << "rat " << player_number << " is hungry" << std::endl;

	if (saturation == 0)
	{
		std::cout << "Rat #" << player_number << " died of hunger." << std::endl;
		dead = true;
	}

}

void Player::teleport_to_entrence()
{
	Map* map_ptr = topography->get_map_array();
	
	set_cords(
		map_ptr[topography->get_current_map_id()].get_door(0).get_x() * 64 - crop_rect.w,
		map_ptr[topography->get_current_map_id()].get_door(0).get_y() * 64 - crop_rect.h
	);
}

Player::Player()
{
	dead = false;
	item_type = 0;

	saturation = 100;

	file_path = "meta_textures/place_holder.png";
	item_search_id = 0;
	has_goal = false;

	is_moving = false;

	keys[0] = SDL_SCANCODE_W;
	keys[1] = SDL_SCANCODE_S;
	keys[2] = SDL_SCANCODE_A;
	keys[3] = SDL_SCANCODE_D;

	moveSpeed = 200.0f;

	wait = false;

	searchCounter = rand() % 100;
	searchCounter /= 100.0f;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}


void Player::set_cords_frames(int x, int y, int framesX, int framesY)
{
	position_rect.x = x;
	position_rect.y = y;

	texture_width = crop_rect.w;

	crop_rect.w /= framesX;
	crop_rect.h /= framesY;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;
}

void Player::set_player_number(int number)
{
	player_number = number;
}

void Player::set_Topography(Topography* h)
{
	topography = h;
}

void Player::set_random_pointer(Random& random)
{
	random_ptr = &random;
}


void Player::Update(float delta, const Uint8* keyState, int mode, Player& front_rat)
{
	// ==================================================== // initialisation
	map_array = topography->get_map_array();
	map_array_size = topography->get_map_size();

	tile_array = topography->get_tile_array();
	tile_array_size = topography->get_tile_size();

	item_array = topography->get_item_array();
	item_array_size = topography->get_item_size();

	int rat_x = this->get_origin_x();
	int rat_y = this->get_origin_y();

	// focus point of a non-player rat.
	// maybe put this inside the function that makes 
	// the cords to it to stand and hole items
	int frontRatX = front_rat.get_origin_x();	
	int frontRatY = front_rat.get_origin_y();

	std::pair <int, int> offests = direction_to_offset(front_rat.GetDirection());

	rat_x += offests.first;
	rat_y += offests.second;


	/*
	float dist1 = sqrt(pow(abs(front_rat.get_origin_x() - rat_x), 2) + pow(abs(front_rat.get_origin_y() - rat_y), 2));
	float dist2 = sqrt(pow(abs(front_rat.get_origin_x() - rat_x), 2) + pow(abs(front_rat.get_origin_y() - rat_y), 2));
	*/

	std::vector<std::vector<bool>> collision_map;

	init_colision_map(collision_map);
	
	if (is_item_available_on_map())
	{
		make_goal();	// make it so: goal = make_goal();
	}
	else
	{
		mode = 0;
	}

	// ============================================================== //

	if (dead)
	{
		return;
	}

	// food tick system: 

	food_tick();

	if (wants_enter_door && (player_number == 0))
	{
		// colision with door check
		int door_check = check_door(topography, map_array, map_array_size, tile_array, tile_array_size);
	}

	// collsion_direction = check_collision()
	collision_map = get_blocked_array(tile_array, tile_array_size);

	
	// ================================================ // make players move
	
	player_move move = { keyState[keys[0]], keyState[keys[1]], keyState[keys[2]], keyState[keys[3]] };

	// player 1
	if (player_number == 0)//--------------------Player control
	{
		make_player_move(move, delta);
	}
	// player 2 & 3
	else  
	{
		if (!wait)
		{
			//find item control
			if (mode == 1 && !holds_item)
			{
				follow_goal(rat_x, rat_y, goalX, goalY, delta, item_array[item_search_id]);
			}
			// autopilot 
			else if (mode == 1 && holds_item)
			{
				follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, delta, front_rat);

			}
			else if (mode == 0 )
			{
				follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, delta, front_rat);
			}
		}
	}

	// make item visible on a player
	if (holds_item)
	{
		hold_item_in_mouth(item_array[item_hold_id]);
	}

	// make movement in texture for player
	if (is_moving)
	{
		frameCounter += delta;
		searchCounter += delta;
		if (wait) waitCounter += delta;


		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			crop_rect.x += frame_width;
			if (crop_rect.x >= texture_width)
				crop_rect.x = 0;
		}

		if (searchCounter >= 2.0f)
		{
			searchCounter = 0;
			wait = true;
		}

		if (waitCounter >= 0.5f)
		{
			waitCounter = 0;
			wait = false;
		}

	}
	else
	{
		frameCounter = 0;
		crop_rect.x = frame_width;
	}
}

void Player::Draw(SDL_Renderer* renderTarget) { SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect); }

void Player::SetNewGoal(int x, int y) { goalX = x; goalY = y; }

int Player::GetDirection() { return current_direction; }


bool Player::intersectsWithBody(Body& b)
{
	if (sqrt(pow(get_origin_x() - b.get_origin_x(), 2) + pow(get_origin_y() - b.get_origin_y(), 2)) >= radius + b.get_radius())
	{
		return false;
	}
	return true;
}

bool Player::is_item_available_on_map()
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

void Player::make_goal()
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

			std::cout << "p: " << player_number << "gx: " << goalX << " gy: " << goalY << std::endl;

		}

		random_item_number++;

		if (random_item_number == item_array_size - 1) random_item_number = 0;
	}
}

void Player::use_item()
{
	if (item_type == 0)
	{

	}
	else if (item_type == 1)
	{
		saturation = 100;

		holds_item = false;
		item_array[item_hold_id].set_cords(-100, -100);
		item_array[item_hold_id].set_on_map(false);

		std::cout << "yumm!" << std::endl;
		item_type = 0;

	}
}

void Player::place_item()
{
	if (item_type == 0)
	{

	}
	else if (item_type == 1)
	{
		holds_item = false;
		std::cout << "placed!"<<std::endl;
		item_type = 0;

	}
}

void Player::set_has_goal(bool value){ has_goal = value; }

void Player::set_enter(bool value){ wants_enter_door = value; }

