#include "Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
	is_entrance = false;
	is_exit = false;
	is_hole = false;

	filePath = "meta_textures/place_holder.png";
}
Tile::Tile(const Tile& other)
{
	std::cout << "other" << std::endl;
	is_exit = other.is_exit;
	is_entrance = other.is_entrance;
	is_hole = other.is_hole;

	filePath = other.filePath;

	this->hight = other.hight;

	this->ptr_renderer = other.ptr_renderer;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Body Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
		if (texture == NULL)
			std::cout << "Error Body Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = other.originX;
	positionRect.y = other.originY;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;
}

Tile::Tile(bool exit, bool entrance, bool hole, std::string path, int height)
{
	is_exit = exit;
	is_entrance = entrance;
	is_hole = hole;

	filePath = path;

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

	this->positionRect = rhs.positionRect;
	this->cropRect = rhs.cropRect;

	return *this;
}

*/

