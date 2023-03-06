#include "Item.h"

Item::Item()
{	filePath = "meta_textures/place_holder.png";
#
	is_on_map = false;
	is_picked_up = false;

	std::cout << "const" << std::endl;
}

Item::Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y)
{
	is_on_map = false;
	is_picked_up = false;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Item Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error Item Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	//isActive = false;
}

Item::Item(Item& other)
{
	std::cout << "copy" << std::endl;

	is_on_map = other.is_on_map;
	is_picked_up = other.is_picked_up;

	filePath = other.filePath;
	ptr_renderer = other.ptr_renderer;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Item Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
		if (texture == NULL)
			std::cout << "Error Item Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = other.positionRect.x;
	positionRect.y = other.positionRect.y;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;
}

Item::~Item()
{
	SDL_DestroyTexture(texture);
}

Item& Item::operator=(Item& other)
{
	std::cout << "=" << std::endl;

	is_on_map = other.get_on_map();
	is_picked_up = other.get_pick_up();

	filePath = other.filePath;
	ptr_renderer = other.ptr_renderer;

	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Item Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
		if (texture == NULL)
			std::cout << "Error Item Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	positionRect.x = other.positionRect.x;
	positionRect.y = other.positionRect.y;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	return *this;
}
	
//void Item::Update(float delta) { }

void Item::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

bool Item::get_on_map() { return is_on_map; }

void Item::set_on_map(bool value) { is_on_map = value; }

void Item::set_pick_up(bool value)
{
	is_picked_up = value;
}

bool Item::get_pick_up()
{
	return is_picked_up;
}


