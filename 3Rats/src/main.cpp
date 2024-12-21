#include "../src/init.h"

int Body::current_index = 0; 
    
std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> LoadTexture(std::string filePath, SDL_Renderer* renderTarget)
{
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture(nullptr, SDL_DestroyTexture);
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == NULL) {
        std::cout << "[Main]: Error loading surface: " << IMG_GetError() << std::endl;
    } else {
        texture.reset(SDL_CreateTextureFromSurface(renderTarget, surface));
        if (texture == NULL) {
            std::cout << "[Main]: Error creating texture from surface: " << SDL_GetError() << std::endl;
        } else {
            std::cout << "[Main]: Texture loaded successfully from: " << filePath << std::endl;
        }
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "[Main]: SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

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
        std::cerr << "[Main]: Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderTarget(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (renderTarget == nullptr) {
        std::cerr << "[Main]: Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Additional debug for resolution
    int levelWidth = 0, levelHeight = 0;
    SDL_GetRendererOutputSize(renderTarget.get(), &levelWidth, &levelHeight);
    
    std::cout << "[Main]: Renderer output size: " << levelWidth << "x" << levelHeight << std::endl;

    // Initialize game objects using Init class
    Seed_manager seed_manager;
    int seedInput = seed_manager.worldSeedGeneration(false); // false = normal generation
    uint32_t seed = seed_manager.generateSeed(seedInput);
    Random random(seed);
    
    // Initialize game objects using Init class
    Init gameInit(
        renderTarget.get(), 
        random, seed, 
        Main_Constants::SCREEN_WIDTH, 
        Main_Constants::SCREEN_HEIGHT);

    Fade fade;
    gameInit.init_fade(&fade);

    int a;
    std::cin >> a;

    Pause pause;
    gameInit.init_pause(&pause);

    a;
    std::cin >> a;

    Clock clock;
    Overlay overlay;
    gameInit.init_clock(&clock, &fade, &overlay);

    a;
    std::cin >> a;

    gameInit.init_overlay(&fade, &clock, &overlay);

    a;
    std::cin >> a;

    // Initialize game entities and maps
    Item item_array[Main_Constants::ITEM_AMOUNT];
    gameInit.init_item_array(
        item_array, Main_Constants::ITEM_AMOUNT
    );

    a;
    std::cin >> a;

    Tile tile_array[Main_Constants::TILE_AMOUNT];
    gameInit.init_tile_array(
        tile_array, Main_Constants::TILE_AMOUNT
    );

    a;
    std::cin >> a;

    std::unique_ptr<Map> map_array[Main_Constants::MAP_AMOUNT];
    gameInit.init_map_array(
        tile_array, Main_Constants::TILE_AMOUNT, 
        item_array, Main_Constants::ITEM_AMOUNT, 
        map_array, Main_Constants::MAP_AMOUNT
    );

    a;
    std::cin >> a;

    Topography topography;
    gameInit.init_topography(map_array, Main_Constants::MAP_AMOUNT, &topography);

    a;
    std::cin >> a;

    Acteur player_array[Main_Constants::PLAYER_AMOUNT];
    gameInit.init_player_array(player_array, Main_Constants::PLAYER_AMOUNT, topography);

    a;
    std::cin >> a;

    Acteur entity[Main_Constants::ENTITY_AMOUNT];
    gameInit.init_entity(entity, Main_Constants::ENTITY_AMOUNT, topography);

    a;
    std::cin >> a;

    // Collage and texture loading
    //Texture_Manager texture_manager;
    auto texture = LoadTexture(
        Texture_Constants::BACKGROUND,
        renderTarget.get()
    );

    if (!texture) {
        std::cout << "[Main]: Failed to load texture." << std::endl;
        SDL_Quit();
        return 1;
    }
    SDL_QueryTexture(texture.get(), NULL, NULL, &levelWidth, &levelHeight);

    Game game(
        renderTarget.get(), texture.get(), 
        topography, 
        player_array, Main_Constants::PLAYER_AMOUNT,
        entity, Main_Constants::ENTITY_AMOUNT, 
        item_array, Main_Constants::ITEM_AMOUNT, 
        tile_array, Main_Constants::TILE_AMOUNT, 
        levelWidth, levelHeight, 
        pause, clock, 
        fade, overlay
);
    
    // Game loop variables
    bool isRunning = true;
    SDL_Event ev;
    int currentTime = 0, prevTime = 0;
    float delta = 0.0f;
    const Uint8* keyState;
    int mode = 0;

    std::cout << "[Main]: Entering game loop..." << std::endl;

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
                handle_key_event(
                    ev, 
                    player_array, Main_Constants::PLAYER_AMOUNT,
                    entity, 
                    mode,
                    fade, 
                    pause
                );
            }
        }

        keyState = SDL_GetKeyboardState(NULL);

        // Update and render the game
        game.update(delta, keyState, mode);
        game.render();

        SDL_RenderPresent(renderTarget.get());

        //int a;
        //std::cin >> a;
    }

    // Freeing the memory
    std::cout << "[Main]: Cleaning up resources..." << std::endl;

    IMG_Quit();
    SDL_Quit();

    return 0;
}
