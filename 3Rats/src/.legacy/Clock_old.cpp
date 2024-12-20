#include "Clock.h"

Clock::Clock(SDL_Renderer* renderTarget, std::string filePath, int x, int y, int framesX, int framesY)
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

	static int ClockNumber = 0;
	ClockNumber++;

	clockCounter = 0;
}

void Clock::Update(float delta, float wait, bool zen,int *time)
{
	clockCounter += delta;

	if (clockCounter >= wait)
	{
		clockCounter = 0;
		min++;
	}

	if (min == 60)
	{
		min = 0;
		hou++;
	}

	int minEin = min % 10;
	int minZen = min - minEin;

	int houEin = hou % 10;
	int houZen = hou - houEin;

	//std::cout << houZen << houEin << ":" << minZen << minEin << std::endl;

	if (zen = true && minEin == 6) 
	{
		minEin = 0;
	}

	switch (minEin) 
	{
	case 0: 
		cropRect.x = frameWidth * 9;
		break;
	case 1:
		cropRect.x = frameWidth * 0;
		break;
	case 2:
		cropRect.x = frameWidth * 1;
		break;
	case 3:
		cropRect.x = frameWidth * 2;
		break;
	case 4:
		cropRect.x = frameWidth * 3;
		break;
	case 5:
		cropRect.x = frameWidth * 4;
		break;
	case 6:
		cropRect.x = frameWidth * 5;
		break;
	case 7:
		cropRect.x = frameWidth * 6;
		break;
	case 8:
		cropRect.x = frameWidth * 7;
		break;
	case 9:
		cropRect.x = frameWidth * 8;
		break;
	default:
		cropRect.x = frameWidth * 9;
	}
}