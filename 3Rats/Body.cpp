#include "Body.h"
#include <memory>

Body::Body()
{
}

Body::~Body()
{
	SDL_DestroyTexture(texture);
}

std::string Body::get_filepath()
{
	return filePath;
}

void Body::set_surface(SDL_Renderer* renderTarget, std::string name)
{
	filePath = name;
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


void Body::set_hight(int value) { this->hight = value; }

int Body::get_hight() { return this->hight; }


void Body::SetX(int x) { positionRect.x = x; }

void Body::SetY(int y) { positionRect.y = y; }



