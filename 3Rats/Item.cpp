#include "Item.h"

Item::Item()
{
	filePath = "place_holder.png";
}

Item::Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
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

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;

	originX = frameWidth / 2;
	originY = frameHeight / 2;

	radius = frameWidth / 2;

	//isActive = false;
	isExisting = true;
}

Item::~Item()
{
	SDL_DestroyTexture(texture);
}

//void Item::Update(float delta) { }

void Item::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

bool Item::GetExistence() { return isExisting; }

void Item::SetExistence(bool value) { isExisting = value; }


