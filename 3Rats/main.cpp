#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include "Item.h"
#include "Body.h"
#include "Map.h"
#include "player.h"
#include "Tile.h"
#include "Random.h"
#include "Hypermap.h"

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

	const int tile_amount = 54;
	const int map_amount = 10;
	const int item_amount = 54;
	const int player_amount = 3;

	int map_number = 0;

	SDL_Init(SDL_INIT_VIDEO);

	if (TTF_Init() < 0)
	{
		std::cout << "Error: " << TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow("3Rats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_hight, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// random object
	Random rand;

	// clock frame
	// ==========================================
	Body clock_frame;
	clock_frame.set_surface(renderTarget, "ui_textures/clock_frame.png");
	clock_frame.set_cords(400, 320);

	// clock object 
	// ==========================================
	// Body* clock_frame_ptr = &clock_frame; // ahhhhh! thats how pointers work
	Clock clock;
	clock.set_renderer(renderTarget);
	clock.load();

	clock.set_up(&clock_frame);
	clock.set_time(16, 30);

	// item array
	// ==========================================
	Item item_array[item_amount];
	Item item;
	item.set_surface(renderTarget);
	item.set_cords(-100, -100);

	for (int i = 0; i < item_amount; i++)
	{
		item_array[i] = item;
	}
	
	// tile array
	// ==========================================
	Tile tile_array[tile_amount];
	Tile tile;
	tile.set_surface(renderTarget);
	tile.set_cords(-100, -100);

	for (int i = 0; i < tile_amount; i++)
	{
		tile_array[i] = tile;
		tile_array[i].set_surface(renderTarget, "meta_textures/place_holder.png");
		tile_array[i].set_cords(-100, -100);
	}
	
	// map array
	// ==========================================
	Map map_array[map_amount];
	Map map;

	map.set_tile_array(tile_array, tile_amount);
	map.set_item_array(item_array, item_amount);

	for (int i = 0; i < map_amount; i++)
	{
		map_array[i] = map;
		map_array[i].set_map_id(i);
	}

	// hypermap object
	// ==========================================

	Hypermap hypermap;

	hypermap.set_renderer(renderTarget);

	hypermap.set_map_array(map_array, map_amount);
	hypermap.set_item_array(item_array, item_amount);
	hypermap.set_tile_array(tile_array, item_amount);

	hypermap.set_up();

	map_array[0].set_type(2);
	map_array[0].show_it();

	for (int i = 1; i < map_amount; i++)
	{
		map_array[i].set_type(rand.flip_coin()); 
		map_array[i].show_it();
	}
	map_array[0].set_textures();

	// player array
	// ==========================================
	Player player_array[player_amount];
	
	for (int i = 0; i < player_amount; i++)
	{
		Player player;
		player.set_player_number(i);
		player.set_hypermap(&hypermap);
		player_array[i] = player;
	}

	player_array[0].set_surface(renderTarget, "player_textures/mango.png");
	player_array[0].set_cords(32, 32, 3, 4);

	player_array[1].set_surface(renderTarget, "player_textures/fridolin.png");
	player_array[1].set_cords(32, 32, 3, 4);

	player_array[2].set_surface(renderTarget, "player_textures/remy.png");
	player_array[2].set_cords(400, 300, 3, 4);

	// ==========================================


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
				case SDLK_u:
					player_array[1].use_item();
					player_array[2].use_item();
					player_array[0].set_enter(false);
					break;

				case SDLK_r:
					player_array[0].SetX(0);
					player_array[0].SetY(0);
					player_array[0].set_enter(false);
					break;

				case SDLK_p:
					player_array[1].place_item();
					player_array[2].place_item();
					player_array[0].set_enter(false);
					break;

				case SDLK_n:
					player_array[1].set_has_goal(false);
					player_array[2].set_has_goal(false);
					player_array[0].set_enter(false);

					break;
				case SDLK_e:
					player_array[0].set_enter(true);
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);


		// update 
		hypermap.update(delta);

		player_array[0].Update(delta, keyState, mode, player_array[0], map_array, map_amount, map_number);
		for (int i = 1; i < player_amount; i++)
		{
			player_array[i].Update(delta, keyState, mode, player_array[i - 1], map_array, map_amount, map_number);
		}

		clock.update(delta);

		SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

		// Drawing the curent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, NULL, NULL);

		// draw 
		hypermap.draw(renderTarget);

		for (int i = 0; i < player_amount; i++)
		{
			player_array[i].Draw(renderTarget);
		}

		clock.draw(renderTarget);

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