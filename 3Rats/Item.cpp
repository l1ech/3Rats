#include "Item.h"

Item::Item(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
{
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

	static int ItemNumber = 0;
	ItemNumber++;

	this->ItemNumber = ItemNumber;

	isExisting = true;
}

Item::~Item()
{
	SDL_DestroyTexture(texture);
}

void Item::Update(float delta)
{	
}

void Item::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

int Item::GetOriginX() { return positionRect.x + originX; }
int Item::GetOriginY() { return positionRect.y + originY; }
int Item::GetRadius() { return radius; }
bool Item::GetExistence() { return isExisting; }

void Item::SetExistence(bool value) { isExisting = value; }

void Item::SetX(int x) { positionRect.x = x; }
void Item::SetY(int y) { positionRect.y = y; }



