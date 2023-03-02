#include "Player.h"

std::vector<std::vector<bool>> Player::get_blocked_array(Tile* arg, int length)
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
		if (intersectsWithBody(arg[i]))
		{
			if (arg[i].get_hight() == 1)
			{

				int delta_x = arg[i].GetOriginX() - positionRect.x;
				int delta_y = arg[i].GetOriginY() - positionRect.y;

				if (delta_x > 0) block.right = true;
				else if (delta_x < 0) block.left = true;

				if (delta_y > 0) block.down = true;
				else if (delta_y < 0) block.up = true;

				blocked_i[i][0] = block.right;
				blocked_i[i][1] = block.left;
				blocked_i[i][2] = block.down;
				blocked_i[i][3] = block.up;
			}
			else if (arg[i].get_hight() == 0)
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

void Player::calculate_blocked_side(break_direction_counter& counter, std::vector<std::vector<bool>> blocked_i, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (blocked_i[i][k])
			{
				if		(k == 0) counter.right++;
				else if (k == 1) counter.left++;
				else if (k == 2) counter.down++;
				else if (k == 3) counter.up++;
				else {}
			}
			else
			{
				if		(k == 0) counter.right--;
				else if (k == 1) counter.left--;
				else if (k == 2) counter.down--;
				else if (k == 3) counter.up--;
				else {}
			}
		}
	}
}

void Player::get_direction_blocked(break_direction_counter& counter, break_direction& direction, int length)
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

Player::Player()
{
	filePath = "place_holder.png";

	block_up = false;
	block_right = false;
	block_down = false;
	block_left = false;

	isActive = false;

	keys[0] = SDL_SCANCODE_W;
	keys[1] = SDL_SCANCODE_S;
	keys[2] = SDL_SCANCODE_A;
	keys[3] = SDL_SCANCODE_D;

	moveSpeed = 200.0f;

	search = false;
	bananPicked = false;
	found = false;
	wait = false;

	searchCounter = rand() % 100;
	searchCounter /= 100.0f;
}

Player::Player(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
	block_up = false;
	block_right = false;
	block_down = false;
	block_left = false;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	isActive = false;

	keys[0] = SDL_SCANCODE_W;
	keys[1] = SDL_SCANCODE_S;
	keys[2] = SDL_SCANCODE_A;
	keys[3] = SDL_SCANCODE_D;
	
	moveSpeed = 200.0f;

	search = false;
	bananPicked = false;
	found = false;
	wait = false;

	searchCounter = rand() % 100;
	searchCounter /= 100.0f;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}


void Player::set_cords(int x, int y, int framesX, int framesY)
{
	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;
}

void Player::set_player_number(int number)
{
	player_number = number;
}


void Player::Update(float delta, const Uint8* keyState, int mode, Player& p, Item& i, int& banan, Tile arg[], int length, Map* map_array, int& map_number)
{
	//std::cout << "x: " << positionRect.x << "|y: " << positionRect.y << std::endl;
	isActive = true;

	int ratX = this->GetOriginX();
	int ratY = this->GetOriginY();

	int frontRatX = p.GetOriginX();
	int frontRatY = p.GetOriginY();

	switch (p.GetDirection()) {
	case 0:
		ratY -= 55;
		break;
	case 1:
		ratY += 55;
		break;
	case 2:
		ratX -= 55;
		break;
	case 3:
		ratX += 55;
		break;
	default:
		break;
	}

	float dist1 = sqrt(pow(abs(p.GetOriginX() - ratX), 2) + pow(abs(p.GetOriginY() - ratY), 2));
	float dist2 = sqrt(pow(abs(p.GetOriginX() - ratX), 2) + pow(abs(p.GetOriginY() - ratY), 2));

	//collision detection and movement options

	std::vector<std::vector<bool>> blocked_i(length, std::vector<bool>(4));

	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			blocked_i[i][k] = false;
		}
	}

	// colision with door check
	// check_door(map_nummber, map_array, arg, length);

	for (int i = 0; i < length; i++)
	{
		if (intersectsWithBody(arg[i]))
		{
			if (arg[i].is_exit)
			{
				positionRect.x = 0;
				positionRect.y = 0;

				map_number++;
				map_array[map_number].set_textures();
			}
			if (arg[i].is_entrance && map_number != 0 && !1)	// disabled for testing
			{
				positionRect.x = 0;
				positionRect.y = 0;

				map_number--;
				map_array[map_number].set_textures();
			}
			else
			{

			}
		}
	}

	// collision with wall detection => blocked_i

	blocked_i = get_blocked_array(arg, length);

	// calculate what side is blocked
	
	break_direction_counter counter = { 0, 0, 0, 0 };

	calculate_blocked_side(counter, blocked_i, length);

	break_direction direction = { 0, 0, 0, 0 };

	get_direction_blocked(counter, direction, length);

	// make players move
	// player 1
	if (player_number == 0)//--------------------Player control
	{
		if (keyState[keys[0]] && !block_up)	//up
		{
			positionRect.y -= moveSpeed * delta;
			cropRect.y = frameHeight * 3;
			direction_rat = 0;
		}
		else if (keyState[keys[1]] && !block_down)			//down
		{
			positionRect.y += moveSpeed * delta;
			cropRect.y = 0;
			direction_rat = 1;
		}
		else if (keyState[keys[2]] && !block_left)			//left
		{
			positionRect.x -= moveSpeed * delta;
			cropRect.y = frameHeight;
			direction_rat = 2;
		}
		else if (keyState[keys[3]] && !block_right)			//right
		{
			positionRect.x += moveSpeed * delta;
			cropRect.y = frameHeight * 2;
			direction_rat = 3;
		}
		else
			isActive = false;
	}
	// player 2 & 3
	else  
	{
		switch (mode)
		{
		case 1://--------------------Ai control
			if (!wait)
			{
				if (ratY > goalY && !block_up)
				{
					positionRect.y -= moveSpeed * delta;
					cropRect.y = frameHeight * 3;
					direction_rat = 0;
				}
				else if (ratY < goalY && !block_down)
				{
					positionRect.y += moveSpeed * delta;
					cropRect.y = 0;
					direction_rat = 1;
				}
				else if (ratX > goalX && !block_left)
				{
					positionRect.x -= moveSpeed * delta;
					cropRect.y = frameHeight;
					direction_rat = 2;
				}
				else if (ratX < goalX && !block_right)
				{
					positionRect.x += moveSpeed * delta;
					cropRect.y = frameHeight * 2;
					direction_rat = 3;
				}
				else if (ratX == goalX && ratY == goalY)
				{
					std::cout << "found!";
					i.SetExistence(false);
					bananPicked = true;
					found = true;
					banan++;
				}
			}
			break;

		case 0://--------------------Follow control (autopilot)

			if (!wait)
			{
				if (ratY > frontRatY && !block_up)
				{
					positionRect.y -= moveSpeed * delta;
					cropRect.y = frameHeight * 3;
					direction_rat = 0;
				}
				else if (ratY < frontRatY && !block_down)
				{
					positionRect.y += moveSpeed * delta;
					cropRect.y = 0;
					direction_rat = 1;
				}
				else if (ratX > frontRatX && !block_left)
				{
					positionRect.x -= moveSpeed * delta;
					cropRect.y = frameHeight;
					direction_rat = 2;
				}
				else if (ratX < frontRatX && !block_right)
				{
					positionRect.x += moveSpeed * delta;
					cropRect.y = frameHeight * 2;
					direction_rat = 3;
				}
				else
				{
					direction_rat = p.GetDirection();
				}

				if (direction_rat == 0) cropRect.y = frameHeight * 3;
				if (direction_rat == 1) cropRect.y = 0;
				if (direction_rat == 2) cropRect.y = frameHeight;
				if (direction_rat == 3) cropRect.y = frameHeight * 2;
			}
			break;
		}
	}

	// make item visible on a player
	if (bananPicked)
	{

		if (direction_rat == 0)
		{
			i.SetX(GetOriginX() - 24);
			i.SetY(GetOriginY() - 32 - 14);
		}
		else if (direction_rat == 1)
		{
			i.SetX(GetOriginX() - 24);
			i.SetY(GetOriginY() - 32 + 14);
		}
		else if (direction_rat == 2)
		{
			i.SetX(GetOriginX() - 24 - 14);
			i.SetY(GetOriginY() - 32);
		}
		else if (direction_rat == 3)
		{
			i.SetX(GetOriginX() - 24 + 14);
			i.SetY(GetOriginY() - 32);
		}

	}

	// make movement in texture for player
	if (isActive)
	{
		frameCounter += delta;
		searchCounter += delta;
		if (wait) waitCounter += delta;


		if (frameCounter >= 0.25f)
		{
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth)
				cropRect.x = 0;
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
		cropRect.x = frameWidth;
	}

	// when there is a item make the goal be theyr x and y
	if (i.GetExistence())
	{
		SetNewGoal(i.GetOriginX(), i.GetOriginY());
	}
	// when the item is found make a new goal 

	else if (found)
	{
		found = false;
		SetNewGoal();
	}
}

void Player::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}


void Player::SetNewGoal()
{
	goalX = rand() % 600;
	goalY = rand() % 400;
}

void Player::SetNewGoal(int x, int y)
{
	goalX = x;
	goalY = y;
}


int Player::GetDirection() { return direction_rat; }


bool Player::intersectsWithBody(Body& b)
{
	if (sqrt(pow(GetOriginX() - b.GetOriginX(), 2) + pow(GetOriginY() - b.GetOriginY(), 2)) >= radius + b.GetRadius())
	{
		return false;
	}
	return true;
}
