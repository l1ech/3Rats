#include "Player.h"

void Player::setup_blocked(std::vector<std::vector<bool>>& vect, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		for (int k = 0; k < w; k++)
		{
			vect[i][k] = false;
		}
	}
}

bool Player::get_end_door_collision(Tile tiles[], std::vector<std::vector<bool>>& vect, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		if (intersectsWithBody(tiles[i]))
		{
			if (tiles[i].is_exit)
			{
				std::cout <<"exit: " << tiles[i].is_exit << std::endl;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool Player::get_entry_door_collision(Tile tiles[], std::vector<std::vector<bool>>& vect, int h, int w)
{
	for (int i = 0; i < h; i++)
	{
		if (intersectsWithBody(tiles[i]))
		{
			if (tiles[i].is_entrance)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
}

Player::Player()
{
	filePath = "place_holder.png";

	block_down, block_left, block_right, block_up = false;

	b_right = 0;
	b_left = 0;
	b_down = 0;
	b_up = 0;

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
	block_down, block_left, block_right, block_up = false;

	b_right = 0;
	b_left = 0;
	b_down = 0;
	b_up = 0;

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


void Player::set_surface(SDL_Renderer* renderTarget, std::string name)
{
	ptr_renderer = renderTarget;
	filePath = name;

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


void Player::Update(float delta, const Uint8* keyState, int mode, Player& p, Item& i, int& banan, Tile tiles[], int length, Map* map_array, int& map_number)
{
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

	// _ collision detection and movement options
	
	// make collision array and set it up
	int height = length;
	int width = 4;

	std::vector<std::vector<bool>> blocked_i;
	blocked_i.resize(height, std::vector<bool>(width));

	setup_blocked(blocked_i, height, width);

	// check if collision with one of the doors
	if (get_end_door_collision(tiles, blocked_i, height, width) && map_number != length)
	{
		positionRect.x = 0;
		positionRect.y = 0;

		map_number++;
		map_array[map_number].set_textures();
	}

	/*
	if (get_entry_door_collision(tiles, blocked_i, height, width) && map_number != 0 )	// disabled for testing
	{
		positionRect.x = 0;
		positionRect.y = 0;

		map_number--;
		map_array[map_number].set_textures();
	}
	*/

	for (int i = 0; i < length; i++)
	{
		if (intersectsWithBody(tiles[i]))
		{
			if (tiles[i].is_exit)
			{
				positionRect.x = 0;
				positionRect.y = 0;

				map_number++;
				map_array[map_number].set_textures();
			}
			if (tiles[i].is_entrance && map_number != 0 && !1)	// disabled for testing
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

	
	for (int i = 0; i < length; i++)
	{
		if (intersectsWithBody(tiles[i]))
		{
			if (tiles[i].get_hight() == 1)
			{
				//std::cout << "to high" << std::endl;

				//std::cout << "hight: " << tiles[i].get_hight()<< std::endl;
				//std::cout << "intersects with:"<< i << std::endl;

				int delta_x = tiles[i].GetOriginX() - positionRect.x;
				int delta_y = tiles[i].GetOriginY() - positionRect.y;

				if (delta_x > 0)
				{
					// blockiere rechts
					block_right = true;
				}
				else if (delta_x < 0)
				{
					block_left = true;
				}
				if (delta_y > 0)
				{
					// blockiere rechts
					block_down = true;
				}
				else if (delta_y < 0)
				{
					block_up = true;
				}

				blocked_i[i][0] = block_right;
				blocked_i[i][1] = block_left;
				blocked_i[i][2] = block_down;
				blocked_i[i][3] = block_up;
			}
			else if (tiles[i].get_hight() == 0)
			{

			}
		}
	}

	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (blocked_i[i][k])
			{
				switch (k)
				{
				case 0:
					b_right++;
					break;

				case 1:
					b_left++;
					break;

				case 2:
					b_down++;
					break;

				case 3:
					b_up++;
					break;

				default:
					break;
				}
			}
			else
			{
				switch (k)
				{
				case 0:
					b_right--;
					break;

				case 1:
					b_left--;
					break;

				case 2:
					b_down--;
					break;

				case 3:
					b_up--;
					break;

				default:
					break;
				}
			}
		}
	}

	//std::cout << "right: " << b_right + length << std::endl;

	//std::cout << "left: " << b_left + length << std::endl;

	if (b_right + length == 0)
	{
		block_right = false;
	}
	else
	{
		block_right = true;
	}

	if (b_left + length == 0)
	{
		block_left = false;
	}
	else
	{
		block_left = true;
	}

	if(b_down + length == 0)
	{
		block_down = false;
	}
	else
	{
		block_down = true;
	}

	if (b_up + length == 0)
	{
		block_up = false;
	}
	else
	{
		block_up = true;
	}

	b_right = 0;
	b_left = 0;
	b_down = 0;
	b_up = 0;

	if (player_number == 0)//--------------------Player control
	{
		if (keyState[keys[0]] && !block_up)	//up
		{
			positionRect.y -= moveSpeed * delta;
			cropRect.y = frameHeight * 3;
			direction = 0;
		}
		else if (keyState[keys[1]] && !block_down)			//down
		{
			positionRect.y += moveSpeed * delta;
			cropRect.y = 0;
			direction = 1;
		}
		else if (keyState[keys[2]] && !block_left)			//left
		{
			positionRect.x -= moveSpeed * delta;
			cropRect.y = frameHeight;
			direction = 2;
		}
		else if (keyState[keys[3]] && !block_right)			//right
		{
			positionRect.x += moveSpeed * delta;
			cropRect.y = frameHeight * 2;
			direction = 3;
		}
		else
			isActive = false;
	}
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
					direction = 0;
				}
				else if (ratY < goalY && !block_down)
				{
					positionRect.y += moveSpeed * delta;
					cropRect.y = 0;
					direction = 1;
				}
				else if (ratX > goalX && !block_left)
				{
					positionRect.x -= moveSpeed * delta;
					cropRect.y = frameHeight;
					direction = 2;
				}
				else if (ratX < goalX && !block_right)
				{
					positionRect.x += moveSpeed * delta;
					cropRect.y = frameHeight * 2;
					direction = 3;
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
					direction = 0;
				}
				else if (ratY < frontRatY && !block_down)
				{
					positionRect.y += moveSpeed * delta;
					cropRect.y = 0;
					direction = 1;
				}
				else if (ratX > frontRatX && !block_left)
				{
					positionRect.x -= moveSpeed * delta;
					cropRect.y = frameHeight;
					direction = 2;
				}
				else if (ratX < frontRatX && !block_right)
				{
					positionRect.x += moveSpeed * delta;
					cropRect.y = frameHeight * 2;
					direction = 3;
				}
				else
				{
					direction = p.GetDirection();
				}

				if (direction == 0) cropRect.y = frameHeight * 3;
				if (direction == 1) cropRect.y = 0;
				if (direction == 2) cropRect.y = frameHeight;
				if (direction == 3) cropRect.y = frameHeight * 2;
			}
			break;
		}
	}

	if (bananPicked)
	{

		if (direction == 0)
		{
			i.SetX(GetOriginX() - 24);
			i.SetY(GetOriginY() - 32 - 14);
		}
		else if (direction == 1)
		{
			i.SetX(GetOriginX() - 24);
			i.SetY(GetOriginY() - 32 + 14);
		}
		else if (direction == 2)
		{
			i.SetX(GetOriginX() - 24 - 14);
			i.SetY(GetOriginY() - 32);
		}
		else if (direction == 3)
		{
			i.SetX(GetOriginX() - 24 + 14);
			i.SetY(GetOriginY() - 32);
		}

	}

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

	if (i.GetExistence())
	{
		SetNewGoal(i.GetOriginX(), i.GetOriginY());
	}
	else if (found)
	{
		found = false;
		SetNewGoal();
	}
	else
	{
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


int Player::GetDirection() { return direction; }


bool Player::intersectsWithBody(Body& b)
{
	if (sqrt(pow(GetOriginX() - b.GetOriginX(), 2) + pow(GetOriginY() - b.GetOriginY(), 2)) >= radius + b.GetRadius())
	{
		return false;
	}
	return true;
}
