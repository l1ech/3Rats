#include "core/init.h"

std::ofstream sdlLogFile;

int Body::current_index = 0; 
int Map::current_index = 0;

void initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL could not initialize! SDL_Error: %s", SDL_GetError());
        throw std::runtime_error("SDL initialization failed");
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL initialized successfully.");
    }
}

void initializeTTF() {
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
        throw std::runtime_error("SDL_ttf initialization failed");
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL_ttf initialized successfully.");
    }
}

void initializeImage() {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
        throw std::runtime_error("SDL_image initialization failed");
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: SDL_image initialized successfully.");
    }
}

int main(int argc, char* argv[])
{
    Logger logger;

    //logger.logToFile()

    initializeSDL();
    initializeTTF();
    initializeImage();

    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window
    (
        SDL_CreateWindow(
            "3Rats", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            Main_Constants::SCREEN_WIDTH, 
            Main_Constants::SCREEN_HEIGHT, 
            SDL_WINDOW_SHOWN), SDL_DestroyWindow
        );

    if (window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Window could not be created! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderTarget(
        SDL_CreateRenderer (window.get(), -1, SDL_RENDERER_ACCELERATED), 
        SDL_DestroyRenderer
    );
    
    if (renderTarget == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    // Additional debug for resolution
    int levelWidth = 0, levelHeight = 0;
    SDL_GetRendererOutputSize(renderTarget.get(), &levelWidth, &levelHeight);
    
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Renderer output size: %dx%d", levelWidth, levelHeight);

    // Initialize game objects using Init class
    Seed_manager seed_manager;
    int seedInput = seed_manager.worldSeedGeneration(false); // false = normal generation
    uint32_t seed = seed_manager.generateSeed(seedInput);
    Random random(seed);
    
    // Initialize game objects using Init class
    Init init(
        renderTarget.get(), 
        random, seed, 
        Main_Constants::SCREEN_WIDTH, 
        Main_Constants::SCREEN_HEIGHT
    );

    Fade fade;
    init.init_fade(&fade);

    Pause pause;
    init.init_pause(&pause);

    Clock_Manager clock_manager;
    Time world_time;
    Clock clock;
    Overlay overlay;
    clock_manager.init(init, &clock, &fade, &overlay, &world_time);

    init.init_overlay(&fade, clock_manager.get_clocks(), &overlay);

    // Initialize game entities and maps
    Item item_array[Main_Constants::ITEM_AMOUNT - 1];
    init.init_item_array(item_array);

    Tile tile_array[Main_Constants::TILE_AMOUNT - 1];
    init.init_tile_array(tile_array);

    std::unique_ptr<Map> map_array[Main_Constants::MAP_AMOUNT];
    init.init_map_array(
        tile_array,
        item_array,
        map_array
    );

    Topography topography;
    init.init_topography(map_array, &topography);

    ActeurManager acteurManager;
    Player player_array[Main_Constants::PLAYER_AMOUNT];
    Player entity_array[Main_Constants::ENTITY_AMOUNT];
    acteurManager.init(init, &topography, player_array, entity_array);

    init.init_entity(acteurManager.get_entities(), topography);

    // Collage and texture loading
    //Texture_Manager texture_manager;

    auto texture = LoadTexture(
        Texture_Constants::BACKGROUND,
        renderTarget.get()
    );

    

    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Failed to load texture.");
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(texture.get(), NULL, NULL, &levelWidth, &levelHeight);

    Game game(
        renderTarget.get(), texture.get(), 
        topography, 
        acteurManager, 
        item_array, Main_Constants::ITEM_AMOUNT, 
        tile_array, Main_Constants::TILE_AMOUNT, 
        levelWidth, levelHeight, 
        pause, *clock_manager.get_clocks(), 
        fade, overlay
    );

    // Game loop variables
    bool isRunning = true;
    SDL_Event ev;
    int currentTime = 0, prevTime = 0;
    float delta = 0.0f;
    const Uint8* keyState;
    int mode = 0;

    SDL_Log("[Main]: Entering game loop...");

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
                isRunning = handle_key_event(
                    ev, acteurManager.get_players(), acteurManager.get_entities(), mode, fade, pause
                );
            }
        }

        keyState = SDL_GetKeyboardState(NULL);

        // Update and render the game
        game.update(delta, keyState, mode);
        game.render();

        SDL_RenderPresent(renderTarget.get());
    }

    SDL_Log("[Main]: Cleaning up resources...");

    IMG_Quit();

    //logger.logToFile();  // Redirect SDL logs to file
    logger.resetLog();  // Reset SDL log output to default

    SDL_Quit();
}
