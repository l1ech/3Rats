#include "init.h"

namespace {
    const int TEXT_SIZE = 24;
    const SDL_Color TEXT_COLOR = {255, 0, 0};

    const int FADE_X = 999;
    const int FADE_Y = 999;
    const int FADE_WIDTH = 200;
    const int FADE_HEIGHT = 90;

    const int CLOCK_X = 400;
    const int CLOCK_Y = 320;
    const int CLOCK_WIDTH = 200;
    const int CLOCK_HEIGHT = 90;

    const int ITEM_INITIAL_X = 100;
    const int ITEM_INITIAL_Y = 100;

    const int TILE_INITIAL_X = 100;
    const int TILE_INITIAL_Y = 100;

    const int PLAYER_FRAME_WIDTH = 32;
    const int PLAYER_FRAME_HEIGHT = 32;
    const int PLAYER_FRAME_ROWS = 3;
    const int PLAYER_FRAME_COLUMNS = 4;

    const int ENTITY_INITIAL_X = 100;
    const int ENTITY_INITIAL_Y = 100;
    const int ENTITY_FRAME_ROWS = 1;
    const int ENTITY_FRAME_COLUMNS = 1;
}

Init::Init(SDL_Renderer* renderTarget, Random& random, uint32_t seed, int screenWidth, int screenHeight)
    : renderTarget(renderTarget), random(random), seed(seed), screenWidth(screenWidth), screenHeight(screenHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "[init]: SDL Initialization failed: " << SDL_GetError() << std::endl;
        exit(1);
    } else {
        std::cout << "[init]: SDL initialized successfully." << std::endl;
    }

    if (TTF_Init() < 0) {
        std::cerr << "[init]: SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    } else {
        std::cout << "[init]: SDL_ttf initialized successfully." << std::endl;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG; // Adjust for supported image formats
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "[init]: SDL_image initialization failed: " << IMG_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        exit(1);
    } else {
        std::cout << "[init]: SDL_image initialized successfully." << std::endl;
    }

    if (renderTarget == nullptr) {
        std::cerr << "[init]: Failed to create render target." << std::endl;
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        exit(1);
    } else {
        std::cout << "[init]: Render target created successfully." << std::endl;
    }

    std::cout << "[init]: Initialization of Init class completed." << std::endl;
}

void Init::init_fade(Fade* fade) {
    Collage collage;
    fade->set_name("fade");
    fade->Text::set_renderer(renderTarget);
    fade->Body::set_surface(renderTarget);

    fade->init_text(collage.get_path(0), TEXT_SIZE, TEXT_COLOR, FADE_X, FADE_Y, FADE_WIDTH, FADE_HEIGHT);
    fade->set_texture(collage.get_path(1));
    fade->set_cords(100, 100);
    
    std::cout << "[init]: Fade initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_pause(Pause* pause) {
    Collage collage;
    pause->set_name("fade");
    pause->Text::set_renderer(renderTarget);
    pause->init_text(collage.get_path(0), TEXT_SIZE, TEXT_COLOR, FADE_X, FADE_Y, FADE_WIDTH, FADE_HEIGHT);
    pause->Body::set_surface(renderTarget);
    pause->set_texture(collage.get_path(1));
    pause->set_cords(FADE_X, FADE_Y);
    std::cout << "[init]: Pause initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_clock(Clock* clock, Fade* fade, Overlay* overlay) {
    Collage collage;
    clock->set_name("clock");
    clock->Text::set_renderer(renderTarget);
    clock->init_text(collage.get_path(0), TEXT_SIZE, TEXT_COLOR, CLOCK_X, CLOCK_Y, CLOCK_WIDTH, CLOCK_HEIGHT);
        clock->Body::set_surface(renderTarget);
    clock->set_texture(collage.get_path(9));
    clock->set_cords(CLOCK_X, CLOCK_Y);
    std::cout << "[init]: Clock initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_overlay(Fade* fade, Clock* clock, Overlay* overlay) {
    overlay->init(fade, clock);
    std::cout << "[init]: Overlay initialized with fade and clock." << std::endl;
    std::cout << std::endl;
}

void Init::init_item_array(Item itemArray[], int itemAmount) {
    Collage collage;

    for (int i = 0; i < itemAmount; i++) {
        Item itemTemplate;
        itemTemplate.set_name("item");
        itemTemplate.set_surface(renderTarget);
        itemTemplate.set_texture(collage.get_path(2));
        itemTemplate.set_cords(ITEM_INITIAL_X, ITEM_INITIAL_Y);
        itemArray[i] = itemTemplate;
    }
    std::cout << "[init]: Item array initialized with " << itemAmount << "[init]:  items." << std::endl;
    std::cout << std::endl;
}

void Init::init_tile_array(Tile tileArray[], int tileAmount) {
    Collage collage;
    for (int i = 0; i < tileAmount; i++) {
        Tile tileTemplate;
        tileTemplate.set_name("tile");
        tileTemplate.set_surface(renderTarget);
        tileTemplate.set_texture(collage.get_path(2));
        tileTemplate.set_cords(TILE_INITIAL_X, TILE_INITIAL_Y);
        tileArray[i] = tileTemplate;
    }
    std::cout << "[init]: Tile array initialized with " << tileAmount << " tiles." << std::endl;
}

void Init::init_map_array(Tile* tileArray, int tileAmount, Item* itemArray, int itemAmount, std::unique_ptr<Map>* mapArray, int mapAmount) {
    for (int i = 0; i < mapAmount; i++) {
        Map_Factory::Map_Type mapType = (i == 0) ? Map_Factory::Map_Type::Maze : (random.flip_coin() ? Map_Factory::Map_Type::Cage : 
        
        Map_Factory::Map_Type::Garden);
        mapArray[i] = Map_Factory::createMap(mapType);
        mapArray[i]->set_random_ptr(&random);
        mapArray[i]->set_tile_array(tileArray, tileAmount);
        mapArray[i]->set_item_array(itemArray, itemAmount);
        mapArray[i]->set_random_pointer(random);
        mapArray[i]->set_map_id(i);
        if (i == 0) {
            //mapArray[i]->set_textures();
            // used to be the heartessence of map generation
            // now we need a new aproach
        }
    }
    std::cout << "[init]: Map array initialized with " << mapAmount << "[init]:  maps." << std::endl;
    std::cout << std::endl;
}

void Init::init_topography(std::unique_ptr<Map>* mapArray, int mapAmount, Topography* topography) {
    topography->set_renderer(renderTarget);
    Item* itemPtr = mapArray[0]->get_item_array();
    int itemAmount = mapArray[0]->get_item_size();
    Tile* tilePtr = mapArray[0]->get_tile_array();
    int tileAmount = mapArray[0]->get_tile_size();

    topography->set_map_array(mapArray, mapAmount);
    topography->set_item_array(itemPtr, itemAmount);
    topography->set_tile_array(tilePtr, tileAmount);
    topography->set_random_pointer(random);

    topography->set_up();
    topography->make_maze();

    for (int i = 0; i < mapAmount; i++) {
        if (topography->counter_maps == i) {
            std::cout << "[init]: END GENERATED!" << std::endl;
            break;
        }
        mapArray[i]->set_layout(topography->get_layout(i));
    }
    //mapArray[0]->set_textures();
    std::cout << "[init]: Topography initialized and maze generated." << std::endl;
    std::cout << std::endl;
}

void Init::init_player_array(Acteur playerArray[], int playerAmount, Topography& topography) {
    Collage collage;
    for (int i = 0; i < playerAmount; i++) {
        Acteur player;
        player.set_name("player");
        player.set_controller_number(i);
        player.set_Topography(&topography);
        player.set_random_pointer(random);
        player.set_surface(renderTarget);
        player.set_texture(collage.get_path(2));
        playerArray[i] = player;
    }

    playerArray[0].set_texture(collage.get_path(3));
    playerArray[0].set_cords_frames(PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT, PLAYER_FRAME_ROWS, PLAYER_FRAME_COLUMNS);


    playerArray[1].set_texture(collage.get_path(4));
    playerArray[1].set_cords_frames(PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT, PLAYER_FRAME_ROWS, PLAYER_FRAME_COLUMNS);

    playerArray[2].set_texture(collage.get_path(5));
    playerArray[2].set_cords_frames(PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT, PLAYER_FRAME_ROWS, PLAYER_FRAME_COLUMNS);

    std::cout << "[init]: Player array initialized with " << playerAmount << "[init]:  players." << std::endl;
    std::cout << std::endl;
}

void Init::init_entity(Acteur entityArray[], int entityAmount, Topography& topography) {
    Collage collage;

    for (int i = 0; i < entityAmount; i++) {
        Acteur entity;
        entity.set_controller_number(3 + i);
        entity.set_Topography(&topography);
        entity.set_random_pointer(random);
        entity.set_name("entity");
        entity.set_surface(renderTarget);
        entity.set_texture(collage.get_path(2));
        entityArray[i] = entity;
    }

    entityArray[0].set_surface(renderTarget);
    entityArray[0].set_texture(collage.get_path(6));
    entityArray[0].set_cords_frames(ENTITY_INITIAL_X, ENTITY_INITIAL_Y, ENTITY_FRAME_ROWS, ENTITY_FRAME_COLUMNS);

    std::cout << "[init]: Entity array initialized with " << entityAmount << "[init]:  entities." << std::endl;
    std::cout << std::endl;
}