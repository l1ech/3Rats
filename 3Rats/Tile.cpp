#include "Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
	is_entrance = false;
	is_exit = false;
	is_hole = false;

	file_path = "meta_textures/place_holder.png";
}
Tile::Tile(const Tile& other)
{
	std::cout << "other" << std::endl;
	is_exit = other.is_exit;
	is_entrance = other.is_entrance;
	is_hole = other.is_hole;

	file_path = other.file_path;

	this->hight = other.hight;

	this->ptr_renderer = other.ptr_renderer;

	SDL_Surface* surface = IMG_Load(file_path.c_str());
	if (surface == NULL)
		std::cout << "Error Body Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
		if (texture == NULL)
			std::cout << "Error Body Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

	position_rect.x = other.origin_x;
	position_rect.y = other.origin_y;

	texture_width = crop_rect.w;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;
}

Tile::Tile(bool exit, bool entrance, bool hole, std::string path, int height)
{
	is_exit = exit;
	is_entrance = entrance;
	is_hole = hole;

	file_path = path;

	this->hight = height;
}

Tile::~Tile()
{
	std::cout << "destructor" << std::endl;
}
/*
Tile& Tile::operator=(Tile rhs)
{
	std::cout << "=" << std::endl;
	is_exit = rhs.is_exit;
	is_entrance = rhs.is_entrance;
	is_hole = rhs.is_hole;

	this->hight = rhs.hight;

	this->ptr_renderer = rhs.ptr_renderer;

	this->position_rect = rhs.position_rect;
	this->crop_rect = rhs.crop_rect;

	return *this;
}

*/

