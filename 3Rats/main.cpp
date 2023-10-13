#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */

#include "Item.h"
#include "Body.h"
#include "Map.h"
#include "acteur.h"
#include "Tile.h"
#include "Random.h"
#include "Topography.h"
#include "Text.h"


int world_seed_generation(bool value)
{

	if (value)
	{
		return 0;
	}
	else
	{
		int type_generation;
		int seed_input;

		std::cout << "What type of generation?" << std::endl;
		std::cout << "random seed: 0" << std::endl;
		std::cout << "user input: 1" << std::endl;
		std::cout << "fix seed (testing): 2" << std::endl;
		std::cin >> type_generation;

		switch (type_generation)
		{
		case 0:
			seed_input = 0;
			break;
		case 1:
			std::cin >> seed_input;
			break;
		case 2:
			seed_input = 0;
			break;
		default:
			break;
		}
		return seed_input;
	}
}
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

void init_text_time(SDL_Renderer* render_target, Text* text_time)
{
	text_time->set_renderer(render_target);
	text_time->init_text("fonts/sans.ttf", 24, { 255, 0, 0 });
}

void init_clock_frame(SDL_Renderer* render_target, Body* body)
{
	body->set_surface(render_target);
	body->set_texture("ui_textures/clock_frame.png");
	body->set_cords(400, 320);
}

void init_clock(SDL_Renderer* render_target, Clock* clock, Body* body, Text* text_time)
{
	clock->set_text(text_time);
	clock->set_body(body);
	clock->set_time(16, 30);
}

void init_item_array(SDL_Renderer* render_target, Item item_array[], int item_amount)
{
	Item item_templet;
	item_templet.set_surface(render_target);
	item_templet.set_texture("meta_textures/place_holder.png");
	item_templet.set_cords(-100, -100);

	for (int i = 0; i < item_amount; i++)
	{
		item_array[i] = item_templet;
	}
}

void init_tile_array(SDL_Renderer* render_target, Tile tile_array[], int tile_amount)
{
	Tile tile_templet;
	tile_templet.set_surface(render_target);
	tile_templet.set_texture("meta_textures/place_holder.png");
	tile_templet.set_cords(-100, -100);


	for (int i = 0; i < tile_amount; i++)
	{
		tile_array[i] = tile_templet;
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

void init_map_array(SDL_Renderer* renderTarget, Tile* tile_array, int tile_amount, Item* item_array, int item_amount, Map* map_array, int map_amount, Random& random)
{
	Map map_templet;

	map_templet.set_tile_array(tile_array, tile_amount);
	init_grid_coords(tile_array, tile_amount, map_templet.get_hight(), map_templet.get_width());
	map_templet.set_item_array(item_array, item_amount);
	init_grid_coords(item_array, item_amount, map_templet.get_hight(), map_templet.get_width());
	map_templet.set_random_pointer(random);

	for (int i = 0; i < map_amount; i++)
	{
		map_array[i] = map_templet;
		map_array[i].set_map_id(i);
	}
}

void init_topography(SDL_Renderer* renderTarget, Map* map_ptr, int map_amount, Topography* topography, Random& random )
{
	topography->set_renderer(renderTarget);

	Item* item_ptr = map_ptr[0].get_item_array();
	int item_amount = map_ptr[0].get_item_size();

	Tile* tile_ptr = map_ptr[0].get_tile_array();
	int tile_amount = map_ptr[0].get_tile_size();

	topography->set_map_array(map_ptr, map_amount);
	topography->set_item_array(item_ptr, item_amount);
	topography->set_tile_array(tile_ptr, item_amount);
	topography->set_random_pointer(random);

	topography->set_up();
	topography->make_maze();

	map_ptr[0].set_type(2);

	for (int i = 1; i < map_amount; i++)
	{
		if (topography->counter_maps == i)
		{
			std::cout << "END GENERATED!" << std::endl;
			break;
		}
		map_ptr[i].set_layout(topography->get_layout(i));
		map_ptr[i].set_type(random.flip_coin());
	}
	map_ptr[0].set_textures();
}

void init_acteur_array(SDL_Renderer* render_target, Acteur* acteur_array, int acteur_amount, Topography& topography, Random& random)
{
	for (int i = 0; i < acteur_amount; i++)
	{
		Acteur acteur;
		acteur.set_acteur_number(i);
		acteur.set_Topography(&topography);
		acteur.set_random_pointer(random);
		acteur_array[i] = acteur;
	}

	acteur_array[0].set_surface(render_target);
	acteur_array[0].set_texture("acteur_textures/mango.png");
	acteur_array[0].set_cords_frames(32, 32, 3, 4);

	acteur_array[1].set_surface(render_target);
	acteur_array[1].set_texture("acteur_textures/fridolin.png");
	acteur_array[1].set_cords_frames(32, 32, 3, 4);

	acteur_array[2].set_surface(render_target);
	acteur_array[2].set_texture("acteur_textures/remy.png");
	acteur_array[2].set_cords_frames(400, 300, 3, 4);
}

uint32_t generate_seed(int seed_generation)
{
	Random key_generator;

	uint32_t seed = 1;

	std::cout << "Seed: ";

	switch (seed_generation)
	{
	case 0:
		seed = key_generator.roll_custom_dice(999 * 999);
		break;
	case 1:
		std::cin >> seed;
		break;
	case 2:
		seed = 1;
		break;
	default:
		break;
	}

	std::cout << seed << std::endl;
	return seed;
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
	const int acteur_amount = 3;

	SDL_Init(SDL_INIT_VIDEO);

	if (TTF_Init() < 0)
	{
		std::cout << "Error: " << TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow("3Rats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_hight, SDL_WINDOW_SHOWN);
	renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// ================================ INIT GAME OBJECTS ================================
	// ===================================================================================
	
	int seed_input = world_seed_generation(1); // 1 = testing/ 2 = normal
	
	uint32_t seed = generate_seed(seed_input);
	std::cout << "Seed: " << seed << std::endl;

	// random object
	Random random(seed);

	Text text_time;
	init_text_time(renderTarget, &text_time);

	Body clock_frame;
	init_clock_frame(renderTarget, &clock_frame);

	// Body* clock_frame_ptr = &clock_frame; // ahhhhh! thats how pointers work
	Clock clock;
	init_clock(renderTarget, &clock, &clock_frame, &text_time);

	Item item_array[item_amount];
	init_item_array(renderTarget, item_array, item_amount);

	Tile tile_array[tile_amount];
	init_tile_array(renderTarget, tile_array, tile_amount);

	Map map_array[map_amount];
	init_map_array(renderTarget, tile_array, tile_amount, item_array, item_amount, map_array, map_amount, random);

	Topography topography;
	init_topography(renderTarget, map_array, map_amount, &topography, random);

	Acteur acteur_array[acteur_amount];
	init_acteur_array(renderTarget, acteur_array, acteur_amount, topography, random);

	// ===================================================================================


	SDL_Texture* texture = LoadTexture("backgound.png", renderTarget);
	SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
	
	bool isRunning = true;
	SDL_Event ev;

	while (isRunning)
	{

		if (clock.get_running() == false)
		{
			isRunning = false;
		}

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
					acteur_array[0].use_item();
					acteur_array[1].use_item();
					acteur_array[2].use_item();
					acteur_array[0].set_enter(false);
					break;

				case SDLK_r:
					acteur_array[0].teleport_to_entrence();
					acteur_array[1].teleport_to_entrence();
					acteur_array[2].teleport_to_entrence();
					acteur_array[0].set_enter(false);
					acteur_array[1].set_enter(false);
					acteur_array[2].set_enter(false);
					break;

				case SDLK_p:
					acteur_array[1].place_item();
					acteur_array[2].place_item();
					acteur_array[0].set_enter(false);
					break;

				case SDLK_n:
					acteur_array[1].set_has_goal(false);
					acteur_array[2].set_has_goal(false);
					acteur_array[0].set_enter(false);
					break;
				case SDLK_e:
					acteur_array[0].set_enter(true);
					break;
				case SDLK_t:
					std::cout << "tp next room" << std::endl;
					break;
				case SDLK_z:
					std::cout << "tp prev room" << std::endl;
					break;
				}
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		// =================================== UPDATE GAME ===================================
		// ===================================================================================

		topography.update(delta);

		acteur_array[0].Update(delta, keyState, mode, acteur_array[2]);
		for (int i = 1; i < acteur_amount; i++)
		{
			acteur_array[i].Update(delta, keyState, mode, acteur_array[i - 1]);
		}

		clock.update(delta);

		SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

		// Drawing the curent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, NULL, NULL);

		// ==================================== DRAW GAME ====================================
		// ===================================================================================

		topography.draw(renderTarget);

		for (int i = 0; i < acteur_amount; i++)
		{
			acteur_array[i].Draw(renderTarget);
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