#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

#include "player.h"
#include "Item.h"
#include "Clock.h"
#include "Frame.h"
#include "Menu.h"
#include "Bowl.h"


SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
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

int main(int argc, char* argv[])
{
	// Initiallaizing and loading variables
	SDL_Window* window = nullptr;
	SDL_Renderer* renderTarget = nullptr;
	int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	const Uint8* keyState; 
	int levelWidth, levelHeight;
	int mode = 0;
	bool menuOn = false;
	int bananAmount = 0;
	int hunger = 3;

	int wait = 12.0f;	//12.0f

	int time = 0;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("3Rats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 420, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Item banan(renderTarget, "banan.png", 200, 120, 3, 4);

	Player mango(renderTarget, "mango.png", 200, 200, 3, 4);
	Player fridolin(renderTarget, "fridolin.png", 200, 160, 3, 4);
	Player remy(renderTarget, "remy.png", 200, 120, 3, 4);

	Frame clockFrame(renderTarget, "frame.png", 0, 320, 1, 1);

	Clock clockMinEin(renderTarget, "clock.png", 202, 330, 10, 1);
	Clock clockMinZen(renderTarget, "clock.png", 138, 330, 10, 1);

	Clock clockHouEin(renderTarget, "clock.png", 74, 330, 10, 1);
	Clock clockHouZen(renderTarget, "clock.png", 10, 330, 10, 1);

	Menu menu(renderTarget, "wall.png", 10, 10, 1, 1);

	Bowl foodBowl(renderTarget, "bowlNew.png", 450, 200, 1, 1);


	SDL_Texture* texture = LoadTexture("groundNew2.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
	
	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;
		while (SDL_PollEvent(&ev) != 0)
		{
			// Getting the quit and keyboard events
			if (ev.type == SDL_QUIT)
				isRunning = false;
			else if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym)
				{
				case SDLK_SPACE:
					mode++;
					if (mode == 2) mode = 0;
					break;

				case SDLK_1:
					texture = LoadTexture("wall.png", renderTarget);
					break;
				case SDLK_f:
					if (menuOn) 
					{
						menu.SetTexture(renderTarget, "empty.png");
						menuOn = false;
					} 
					else
					{
						switch (hunger) 
						{
						case 0:
							menu.SetTexture(renderTarget, "menu0.png");
							break;
						case 1:
							menu.SetTexture(renderTarget, "menu1.png");
							break;
						case 2:
							menu.SetTexture(renderTarget, "menu2.png");
							break;
						case 3:
							menu.SetTexture(renderTarget, "menu3.png");
							break;
						}
						menuOn = true;
					}
					break;

				case SDLK_e:

					if (bananAmount >= 1) 
					{
						bananAmount--;
						banan.~Item();
						hunger--;
					}
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		foodBowl.Update(delta);

		banan.Update(delta);

		mango.Update(delta, keyState, mode, mango , banan, bananAmount);
		fridolin.Update(delta, keyState, mode, mango, banan, bananAmount);
		remy.Update(delta, keyState, mode, fridolin, banan, bananAmount);

		clockFrame.Update(delta);

		clockMinEin.Update(delta, wait,				false, &time);
		clockMinZen.Update(delta, wait * 10,		true, &time);
		clockHouEin.Update(delta, wait * 10 * 6,	false, &time);
		clockHouZen.Update(delta, wait * 10 * 60,	true, &time);

		menu.Update(delta, hunger);

		SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

		// Drawing the cuurent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, NULL, NULL);

		//SDL_RenderCopy(renderTarget, text, NULL, &textRect);

		foodBowl.Draw(renderTarget);

		banan.Draw(renderTarget);

		mango.Draw(renderTarget);
		fridolin.Draw(renderTarget);
		remy.Draw(renderTarget);

		clockFrame.Draw(renderTarget);

		clockMinEin.Draw(renderTarget);
		clockMinZen.Draw(renderTarget);
		clockHouEin.Draw(renderTarget);
		clockHouZen.Draw(renderTarget);

		menu.Draw(renderTarget);


		SDL_RenderPresent(renderTarget);
	}

	// Freeing the memory
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyTexture(texture);

	window = nullptr;
	renderTarget = nullptr;
	texture = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;

}