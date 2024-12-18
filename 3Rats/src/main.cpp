#include "../src/init.h"

// Constants

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 420;
const int ITEM_AMOUNT = 54;
const int TILE_AMOUNT = 54;
const int MAP_AMOUNT = 10;
const int PLAYER_AMOUNT = 3;
const int ENTITY_AMOUNT = 1;


const int TELEPORT_WAIT_TIME = 12; // Adjust wait time

int Body::current_index = 0; 

SDL_Texture* LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (surface == NULL)
		std::cout << "Error Surface1" << std::endl;
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
    // Initialize SDL and create a window and renderer
    SDL_Window* window = nullptr;
    SDL_Renderer* renderTarget = nullptr;
    int levelWidth = 0, levelHeight = 0;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    } else {
        std::cout << "SDL initialized successfully." << std::endl;
    }

    // Create a window
    window = SDL_CreateWindow("3Rats", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    } else {
        std::cout << "Window created successfully." << std::endl;
    }

    // Create a renderer
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderTarget == nullptr) {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } else {
        std::cout << "Renderer created successfully." << std::endl;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        std::cout << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderTarget);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } else {
        std::cout << "SDL_ttf initialized successfully." << std::endl;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG; // Adjust for supported image formats
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderTarget);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    } else {
        std::cout << "SDL_image initialized successfully." << std::endl;
    }

    // Additional debug for resolution
    SDL_GetRendererOutputSize(renderTarget, &levelWidth, &levelHeight);
    std::cout << "Renderer output size: " << levelWidth << "x" << levelHeight << std::endl;


	// Initialize game objects using Init class
    Seed_manager seed_manager;
    int seedInput = seed_manager.worldSeedGeneration(false); // false = normal generation
	uint32_t seed = seed_manager.generateSeed(seedInput);
    Random random(seed);
    
	// Initialize game objects using Init class
    Init gameInit(renderTarget, random, seed, SCREEN_WIDTH, SCREEN_HEIGHT);

    Fade fade;
    gameInit.init_fade(&fade);

    Pause pause;
    gameInit.init_pause(&pause);

    Clock clock;
    Overlay overlay;
    gameInit.init_clock(&clock, &fade, &overlay);
    gameInit.init_overlay(&fade, &clock, &overlay);

    // Initialize game entities and maps
    Item item_array[ITEM_AMOUNT];
    gameInit.init_item_array(item_array, ITEM_AMOUNT);

    Tile tile_array[TILE_AMOUNT];
    gameInit.init_tile_array(tile_array, TILE_AMOUNT);

    std::unique_ptr<Map> map_array[MAP_AMOUNT];
    gameInit.init_map_array(tile_array, TILE_AMOUNT, item_array, ITEM_AMOUNT, map_array, MAP_AMOUNT);

    Topography topography;
    gameInit.init_topography(map_array, MAP_AMOUNT, &topography);

    Acteur player_array[PLAYER_AMOUNT];
    gameInit.init_player_array(player_array, PLAYER_AMOUNT, topography);

    Acteur entity[ENTITY_AMOUNT];
    gameInit.init_entity(entity, ENTITY_AMOUNT, topography);

    // Collage and texture loading
    Collage collage;
    SDL_Texture* texture = LoadTexture(collage.get_path(7), renderTarget);
    SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

    // Game loop variables
    bool isRunning = true;
    SDL_Event ev;
    int currentTime = 0, prevTime = 0;
    float delta = 0.0f;
    const Uint8* keyState;
    int mode = 0;
    bool menuOn = false;
    int bananAmount = 0;
    int hunger = 3;
    int wait = TELEPORT_WAIT_TIME; // Adjust wait time

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
				handle_key_event(ev, player_array, entity, mode, fade, pause, PLAYER_AMOUNT);
			}
		}

		keyState = SDL_GetKeyboardState(NULL);

		// =================================== UPDATE GAME ===================================
		// ===================================================================================

		topography.update(delta);

		player_array[0].Update(delta, keyState, mode, player_array[2]);
		for (int i = 1; i < PLAYER_AMOUNT; i++)
		{
			player_array[i].Update(delta, keyState, mode, player_array[i - 1]);
		}

		entity[0].update(delta);
		std::string pause_message = "Pause.";
		pause.update(pause_message);
		clock.update(delta);
		fade.update(std::to_string(clock.get_day()));
		overlay.update(delta);

		SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);

		// Drawing the curent image to the window
		SDL_RenderClear(renderTarget);
		SDL_RenderCopy(renderTarget, texture, NULL, NULL);

		// ==================================== DRAW GAME ====================================
		// ===================================================================================

		topography.draw(renderTarget);

		for (int i = 0; i < PLAYER_AMOUNT; i++)
		{
			player_array[i].Draw(renderTarget);
		}
		entity[0].draw(renderTarget);
		clock.draw(renderTarget);
		fade.draw(renderTarget);
		pause.draw(renderTarget);
		overlay.draw(renderTarget);

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