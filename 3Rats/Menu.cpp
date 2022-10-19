#include "Menu.h"

Menu::Menu(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
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
}

void Menu::SetTexture(SDL_Renderer* renderTarget, std::string filePath)
{
	texture = LoadTexture( renderTarget, filePath);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	textureWidth = cropRect.w;

	cropRect.w /= 1;
	cropRect.h /= 1;

	frameWidth = positionRect.w = cropRect.w;
	frameHeight = positionRect.h = cropRect.h;
}

SDL_Texture* Menu::LoadTexture(SDL_Renderer* renderTarget, std::string filePath)
{
	SDL_Texture* texture = nullptr;
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

	return texture;
}

void Menu::Update(float delta, int hunger)
{
}

void Menu::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}
