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
#include "Level.h"

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

void init_clock_frame(SDL_Renderer* render_target, Body* body)
{
	body->set_surface(render_target, "ui_textures/clock_frame.png");
	body->set_cords(400, 320);
}

void init_clock(SDL_Renderer* render_target, Clock* clock, Body* body)
{
	clock->set_renderer(render_target);
	clock->load();
	clock->set_up(body);
	clock->set_time(16, 30);
}

void init_item_array(SDL_Renderer* render_target, Item item_array[], int item_amount)
{
	Item item_templet;
	item_templet.set_surface(render_target);
	item_templet.set_cords(-100, -100);

	for (int i = 0; i < item_amount; i++)
	{
		item_array[i] = item_templet;
	}
}

void init_tile_array(SDL_Renderer* render_target, Tile tile_array[], int tile_amount)
{
	Tile tile_templet;
	tile_templet.set_surface(render_target);	// doppelt gemoppelt?
	tile_templet.set_cords(-100, -100);

	for (int i = 0; i < tile_amount; i++)
	{
		tile_array[i] = tile_templet;
		tile_array[i].set_surface(render_target, "meta_textures/place_holder.png");
		tile_array[i].set_cords(-100, -100);
	}
}

template<typename T>
void init_grid_coords(T* array, int size, int height, int width)
{
	int x_cord = 0;
	int y_cord = 0;

	int i = 0;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			x_cord = w * 64;
			y_cord = h * 64;
			array[i].set_cords(x_cord, y_cord);
			i++;
		}
	}
}

void init_map_array(SDL_Renderer* renderTarget, Tile* tile_array, int tile_amount, Item* item_array, int item_amount, Map* map_array, int map_amount)
{
	Map map_templet;

	map_templet.set_tile_array(tile_array, tile_amount);
	init_grid_coords(tile_array, tile_amount, map_templet.get_hight(), map_templet.get_width());
	map_templet.set_item_array(item_array, item_amount);
	init_grid_coords(item_array, item_amount, map_templet.get_hight(), map_templet.get_width());


	for (int i = 0; i < map_amount; i++)
	{
		map_array[i] = map_templet;
		map_array[i].set_map_id(i);
	}
}

void init_hyper_map(SDL_Renderer* renderTarget, Map* map_array, int map_amount, Level* Level)
{
	Random random;
	Level->set_renderer(renderTarget);

	Item* item_array = map_array[0].get_item_array();
	int item_amount = map_array[0].get_item_size();

	Tile* tile_array = map_array[0].get_tile_array();
	int tile_amount = map_array[0].get_tile_size();

	Level->set_map_array(map_array, map_amount);
	Level->set_item_array(item_array, item_amount);
	Level->set_tile_array(tile_array, item_amount);

	Level->set_up();
	Level->make_maze();

	map_array[0].set_type(2);
	map_array[0].show_it();

	for (int i = 1; i < map_amount; i++)
	{
		if (Level->counter_maps == i)
		{
			std::cout << "END GENERATED!" << std::endl;
			break;
		}
		map_array[i].set_layout(Level->get_layout(i));
		map_array[i].set_type(random.flip_coin());
		map_array[i].show_it();
	}
	map_array[0].set_textures();
}

void init_player_array(SDL_Renderer* render_target, Player* player_array, int player_amount, Level& Level)
{
	for (int i = 0; i < player_amount; i++)
	{
		Player player;
		player.set_player_number(i);
		player.set_Level(&Level);
		player_array[i] = player;
	}

	player_array[0].set_surface(render_target, "player_textures/mango.png");
	player_array[0].set_cords(32, 32, 3, 4);

	player_array[1].set_surface(render_target, "player_textures/fridolin.png");
	player_array[1].set_cords(32, 32, 3, 4);

	player_array[2].set_surface(render_target, "player_textures/remy.png");
	player_array[2].set_cords(400, 300, 3, 4);
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


	// ================================ INIT GAME OBJECTS ================================
	// ===================================================================================

	// random object
	Random rand;

	Body clock_frame;
	init_clock_frame(renderTarget, &clock_frame);

	// Body* clock_frame_ptr = &clock_frame; // ahhhhh! thats how pointers work
	Clock clock;
	init_clock(renderTarget, &clock, &clock_frame);

	Item item_array[item_amount];
	init_item_array(renderTarget, item_array, item_amount);

	Tile tile_array[tile_amount];
	init_tile_array(renderTarget, tile_array, tile_amount);

	Map map_array[map_amount];
	init_map_array(renderTarget, tile_array, tile_amount, item_array, item_amount, map_array, map_amount);

	Level Level;
	init_hyper_map(renderTarget, map_array, map_amount, &Level);

	Player player_array[player_amount];
	init_player_array(renderTarget, player_array, player_amount, Level);

	// ===================================================================================


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

					player_array[1].SetX(0);
					player_array[1].SetY(0);
					player_array[1].set_enter(false);

					player_array[2].SetX(0);
					player_array[2].SetY(0);
					player_array[2].set_enter(false);
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
		Level.update(delta);

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
		Level.draw(renderTarget);

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