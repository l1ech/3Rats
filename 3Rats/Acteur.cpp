#include "Acteur.h"

std::vector<std::vector<bool>> Acteur::get_blocked_array(Tile* tile_array, int length)
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



void Acteur::make_acteur_move(controller_move move, block_direction direction, float delta)
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


void Acteur::follow(int rat_x, int rat_y, int front_x, int front_y, block_direction direction, float delta, Acteur& p1)
{
	/*
	std::cout	<< "up:" << direction.up
				<< "down:" << direction.down
				<< "left:" << direction.left
				<< "right:" << direction.right
				<< std::endl;

	*/

	if (rat_y > front_y && !direction.up)
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (rat_y < front_y && !direction.down)
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (rat_x > front_x && !direction.left)
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (rat_x < front_x && !direction.right)
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else
	{
		current_direction = p1.GetDirection();
	}

	/*
		if (current_direction == 0) crop_rect.y = frame_height * 3;
	if (current_direction == 1) crop_rect.y = 0;
	if (current_direction == 2) crop_rect.y = frame_height;
	if (current_direction == 3) crop_rect.y = frame_height * 2;
	*/

	
}


void Acteur::follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat)
{
	if (rat_y > front_rat_y && !direction.up)
	{
		position_rect.y -= moveSpeed * delta;
		crop_rect.y = frame_height * 3;
		current_direction = 0;
	}
	else if (rat_y < front_rat_y && !direction.down)
	{
		position_rect.y += moveSpeed * delta;
		crop_rect.y = 0;
		current_direction = 1;
	}
	else if (rat_x > front_rat_x && !direction.left)
	{
		position_rect.x -= moveSpeed * delta;
		crop_rect.y = frame_height;
		current_direction = 2;
	}
	else if (rat_x < front_rat_x && !direction.right)
	{
		position_rect.x += moveSpeed * delta;
		crop_rect.y = frame_height * 2;
		current_direction = 3;
	}
	else
	{
		current_direction = front_rat.GetDirection();
	}

	/*
	if (current_direction == 0) crop_rect.y = frame_height * 3;
	if (current_direction == 1) crop_rect.y = 0;
	if (current_direction == 2) crop_rect.y = frame_height;
	if (current_direction == 3) crop_rect.y = frame_height * 2;
	*/
	
}

void Acteur::follow_goal(int rat_x, int rat_y, int goal_x, int goal_y, block_direction direction, float delta, Prop& prop)
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
	else if (rat_x == goal_x && rat_y == goal_y && !prop.get_pick_up())
	{
		std::cout << "found!" << " p: " << controller_number << "prop number: " << prop_search_id << std::endl;;

		prop_hold_id = prop_search_id;
		holds_prop = true;
		prop.set_pick_up(true);
		has_goal = false;

		prop_type = 1;

	}
	else if (rat_x == goal_x && rat_y == goal_y && prop.get_pick_up())
	{
		std::cout << "did not found!" << " p: " << controller_number << "prop number: " << prop_search_id << std::endl;;
		has_goal = false;
	}
}

void Acteur::hold_prop_in_mouth(Prop& prop)
{
	// add he offsets to make more sense. just for example i did it fo 14
	int offset = 14;

	if (current_direction == 0)
	{
		prop.set_cords(get_origin_x() - 24, get_origin_y() - 32 - offset);
	}
	else if (current_direction == 1)
	{
		prop.set_cords(get_origin_x() - 24, get_origin_y() - 32 + offset);
	}
	else if (current_direction == 2)
	{
		prop.set_cords(get_origin_x() - 24 - offset, get_origin_y() - 32);
	}
	else if (current_direction == 3)
	{
		prop.set_cords(get_origin_x() - 24 + offset, get_origin_y() - 32);
	}
}

Acteur::Acteur()
{
	dead = false;
	prop_type = 0;

	saturation = 100;

	texture_path = "meta_textures/place_holder.png";
	prop_search_id = 0;
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

Acteur::~Acteur()
{
	SDL_DestroyTexture(texture);
}

void Acteur::update(float delta, int mode, Acteur& front_rat)
{
	/*
	 	std::cout << "update con: " << controller_number << std::endl;

		std::cout << "x: " << get_origin_x()
			<< "y: " << get_origin_y() << std::endl;

		if (holds_prop == true) std::cout << "player" << get_controller_number() << "holds prop : true, effect: none" << std::endl;

	*/
	

	//map_array = stage->get_map_array();
	//map_array_size = stage->get_map_size();

	tile_array = map_array->get_tile_array();
	tile_array_size = map_array->get_tile_size();

	prop_array = map_array->get_prop_array();
	prop_array_size = map_array->get_prop_size();

	if (is_prop_available_on_map())
	{
		make_goal();	// make it so: goal = make_goal();
	}
	else
	{
		mode = 0;
	}

	int rat_x = this->get_origin_x();
	int rat_y = this->get_origin_y();

	// focus point of a non-acteur rat.
	// maybe put this inside the function that makes 
	// the cords to it to stand and hole props
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
	block_direction_counter collision_counter = { 0, 0, 0, 0 };
	block_direction direction = { 0, 0, 0, 0 };

	// colision with door check
	//check_door(stage, map_array, map_array_size, tile_array, tile_array_size);

	collision_map = get_blocked_array(tile_array, tile_array_size);

	calculate_blocked_side(collision_counter, collision_map, tile_array_size);

	get_direction_blocked(collision_counter, direction, tile_array_size);

	
	if(controller_number == 1 || controller_number == 2)
	{
		if (!wait)
		{
			//find prop control
			if (mode == 1 && !holds_prop)
			{
				follow_goal(rat_x, rat_y, goalX, goalY, direction, delta, prop_array[prop_search_id]);
			}
			// autopilot 
			else if (mode == 1 && holds_prop)
			{
				follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, direction, delta, front_rat);

			}
			else if (mode == 0)
			{
				follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, direction, delta, front_rat);
			}
		}
	}
	// make prop visible on a acteur
	if (holds_prop)
	{
		hold_prop_in_mouth(prop_array[prop_hold_id]);
	}

	// add pauses so that the bots move more dynamicylly
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

void Acteur::update(float delta, const Uint8* keyState)
{

	//map_array = stage->get_map_array();
	//map_array_size = stage->get_map_size();

	tile_array = map_array->get_tile_array();
	tile_array_size = map_array->get_tile_size();

	prop_array = map_array->get_prop_array();
	prop_array_size = map_array->get_prop_size();

	int rat_x = this->get_origin_x();
	int rat_y = this->get_origin_y();

	std::vector<std::vector<bool>> collision_map;

	init_colision_map(collision_map);
	block_direction_counter collision_counter = { 0, 0, 0, 0 };
	block_direction direction = { 0, 0, 0, 0 };

	// colision with door check
	//check_door(stage, map_array, map_array_size, tile_array, tile_array_size);

	collision_map = get_blocked_array(tile_array, tile_array_size);

	calculate_blocked_side(collision_counter, collision_map, tile_array_size);

	get_direction_blocked(collision_counter, direction, tile_array_size);

	// make acteurs move

	controller_move move = { keyState[keys[0]], keyState[keys[1]], keyState[keys[2]], keyState[keys[3]] };
	/*
	std::cout << "move: " << move.down << move.left << move.right << move.up << std::endl;
	std::cout << "direction blocked: " << direction.down << direction.left << direction.right << direction.up << std::endl;
	std::cout << "direction blocked count: " << collision_counter.down << collision_counter.left << collision_counter.right << collision_counter.up << std::endl;
	*/
	
	// acteur 1
	if (controller_number == 0)//--------------------Acteur control
	{
		make_acteur_move(move, direction, delta);
	}

	// make prop visible on a acteur
	if (holds_prop)
	{
		hold_prop_in_mouth(prop_array[prop_hold_id]);
	}

}

void Acteur::Draw(SDL_Renderer* renderTarget) 
{ 
	std::cout << "draw con: " << controller_number << std::endl;
	SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect); 
}

void Acteur::update(float delta, Acteur& p1)
{
	/*
	std::cout << "update con: " << controller_number << std::endl;

	std::cout << "x: " << get_origin_x()
		<< "y: " << get_origin_y() << std::endl;

	if (holds_prop == true) std::cout << "player" << get_controller_number() << "holds prop : true, effect: none" << std::endl;

	*/

	tile_array = map_array->get_tile_array();
	tile_array_size = map_array->get_tile_size();

	prop_array = map_array->get_prop_array();
	prop_array_size = map_array->get_prop_size();

	
	int x = this->get_origin_x();
	int y = this->get_origin_y();

	// focus on player rat

	int follow_x = p1.get_origin_x() - 1;
	int follow_y = p1.get_origin_y() - 1;

	std::vector<std::vector<bool>> collision_map;

	init_colision_map(collision_map);
	block_direction_counter collision_counter = { 0, 0, 0, 0 };
	block_direction direction = { 0, 0, 0, 0 };

	// colision with door check
	//check_door(stage, map_array, map_array_size, tile_array, tile_array_size);

	collision_map = get_blocked_array(tile_array, tile_array_size);

	calculate_blocked_side(collision_counter, collision_map, tile_array_size);

	get_direction_blocked(collision_counter, direction, tile_array_size);

	// make acteurs move
	

	if (1 == 1) // add more options later 
	{
		follow(x, y, follow_x, follow_y, direction, delta, p1);
	}	
}

bool Acteur::intersectsWithBody(Body& b)
{
	if (
		sqrt(
			pow( get_origin_x() - b.get_origin_x(), 2) 
			+ pow( get_origin_y() - b.get_origin_y(), 2)) 
		>= radius + b.get_radius() )
	{
		return false;
	}
	return true;
}

void Acteur::set_role(int r)
{
	role = r;
}

void Acteur::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}


void Acteur::use_prop()
{
	if (prop_type == 0)
	{

	}
	else if (prop_type == 1)
	{
		saturation = 100;

		holds_prop = false;
		prop_array[prop_hold_id].set_cords(-100, -100);
		prop_array[prop_hold_id].set_on_map(false);

		std::cout << "yumm!" << std::endl;
		prop_type = 0;

	}
}

int Acteur::pick_option()
{
	return random_ptr->roll_custom_dice(4);
}
