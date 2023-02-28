#include "Body.h"
#include <memory>

void Body::set_surface(SDL_Renderer* renderTarget)
{
	ptr_renderer = renderTarget;

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

}

void Body::set_cords(int x, int y)
{
	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;
}

void Body::set_texture(std::string name)
{
	filePath = name;

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

}

Body::Body(const Body& b)
{

	ptr_renderer = b.ptr_renderer;

	//std::cout << "copy constructor aufruf" << std::endl;

	filePath = b.filePath;

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

	positionRect.x = b.originX;
	positionRect.y = b.originY;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

}

Body::Body()
{

	//std::cout << "leerer constructor aufruf" << std::endl;

	filePath = "place_holder.png";
}

Body::Body(int x, int y)
{
	//std::cout << "constructor mit x y aufruf" << std::endl;

	filePath = "place_holder.png";
	positionRect.x = x;
	positionRect.y = y;

}

Body::Body(SDL_Renderer* renderTarget, int x, int y)
{
	
	ptr_renderer = renderTarget;

	//std::cout << "normaler constructor aufruf" << std::endl;

	filePath = "place_holder.png";

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

	positionRect.x = x;
	positionRect.y = y;

	textureWidth = cropRect.w;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;
}

Body::~Body()
{
	SDL_DestroyTexture(texture);
}

void Body::Update(float delta)
{
	//std::cout << "update" << std::endl;
}

void Body::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);	
}

int Body::GetOriginX() { return positionRect.x + originX; }
int Body::GetOriginY() { return positionRect.y + originY; }
int Body::GetRadius() { return radius; }

void Body::set_hight(int value)
{
	this->hight = value;
}

int Body::get_hight()
{
	return this->hight;
}



void Body::SetX(int x) { positionRect.x = x; }
void Body::SetY(int y) { positionRect.y = y; }



