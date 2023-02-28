#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include "Item.h"
#include "Body.h"
#include "Map.h"
#include "player.h"

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderTarget, surface);
		if (texture == NULL)
			std::cout << "Error Texture" << std::endl;
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

	const int screen_width = 600;
	const int screen_hight = 420;

	const int body_amount = 54;
	const int map_amount = 4;
	const int item_amount = 5;

	int map_number = 0;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("3Rats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_hight, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Item item_array[item_amount];

	Item banan;//(renderTarget, "banan.png", 100, 100, 3, 4);
	banan.set_surface(renderTarget);
	banan.set_cords(100, 100);

	for (int i = 0; i < item_amount; i++)
	{
		item_array[i] = banan;
	}
	
	Body body_array[body_amount];
	
	Body body;
	body.set_surface(renderTarget);
	body.set_cords(-100, -100);

	for (int i = 0; i < body_amount; i++)
	{
		body_array[i] = body;
	}
	
	Map map_array[map_amount];

	Map map;
	map.set_body_array(body_array);
	map.set_item_array(item_array, item_amount);

	for (int i = 0; i < map_amount; i++)
	{
		map_array[i] = map;
		map_array[i].set_type(map.flip_coin()); // rand() % 2 - 1	//this is kinda cheating
		map_array[i].show_it();
	}

	map_array[0].set_textures();

	Player mango(renderTarget, "Gregor.png", 32, 32, 3, 4);
	Player fridolin(renderTarget, "Gregor.png", 200, 160, 3, 4);
	Player remy(renderTarget, "Gregor.png", 400, 300, 3, 4);

	SDL_Texture* texture = LoadTexture("backgound.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
	
	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{
		prevTime = currentTime;
		currentTime = SDL_GetTicks();
		delta = (currentTime - prevTime) / 1000.0f;

		while (SDL_PollEvent(&ev) != 0)		// ------------- key-events
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
					break;

				case SDLK_r:
					break;

				case SDLK_g:
					map.set_textures();
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);


		// ------------- update bodys

		for (int i = 0; i < item_amount; i++)
		{
			item_array[i].Update(delta);
		}
		//banan.Update(delta);

		//body.Update(delta);
		//for (int i = 0; i<body_amount; i++)
		//{
		//	bodys.at(i).Update(delta);	//static object does not need update?
		//}

		mango.Update(delta, keyState, mode, mango , banan, bananAmount, body_array, body_amount, map_array, map_number);
		fridolin.Update(delta, keyState, mode, mango, banan, bananAmount, body_array, body_amount, map_array, map_number);
		remy.Update(delta, keyState, mode, fridolin, banan, bananAmount, body_array, body_amount, map_array, map_number);


		SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

		// Drawing the curent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, NULL, NULL);

		//SDL_RenderCopy(renderTarget, text, NULL, &textRect);

		// ------------- draw bodys

		map.Draw(renderTarget);
		banan.Draw(renderTarget);


		mango.Draw(renderTarget);
		fridolin.Draw(renderTarget);
		remy.Draw(renderTarget);

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