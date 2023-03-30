#include "Item.h"

Item::Item()
{	file_path = "meta_textures/place_holder.png";

	is_on_map = false;
	is_picked_up = false;

	//std::cout << "const" << std::endl;
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

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

	position_rect.x = x;
	position_rect.y = y;

	texture_width = crop_rect.w;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;

	//isActive = false;
}

Item::Item(Item& other)
{
	//std::cout << "copy" << std::endl;

	is_on_map = other.is_on_map;
	is_picked_up = other.is_picked_up;

	file_path = other.file_path;
	ptr_renderer = other.ptr_renderer;

	SDL_Surface* surface = IMG_Load(file_path.c_str());
	if (surface == NULL)
		std::cout << "Error Item Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
		if (texture == NULL)
			std::cout << "Error Item Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

	position_rect.x = other.position_rect.x;
	position_rect.y = other.position_rect.y;

	texture_width = crop_rect.w;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;
}

Item::~Item()
{
	SDL_DestroyTexture(texture);
}
/*
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

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

	position_rect.x = other.position_rect.x;
	position_rect.y = other.position_rect.y;

	textureWidth = crop_rect.w;

	frameWidth = position_rect.w = crop_rect.w;
	frameHeight = position_rect.h = crop_rect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	return *this;
}

*/
	
//void Item::Update(float delta) { }

void Item::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect);
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


