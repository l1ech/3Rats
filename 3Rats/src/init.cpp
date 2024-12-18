#include "init.h"

Init::Init(SDL_Renderer* renderTarget, Random& random, uint32_t seed, int screenWidth, int screenHeight)
    : renderTarget(renderTarget), random(random), seed(seed), screenWidth(screenWidth), screenHeight(screenHeight)
{
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        exit(1);  // Exit if SDL fails to initialize
    }
    

    // Optionally initialize SDL_ttf
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // Now that SDL and SDL_image are initialized, you can set up the renderer
    // (assuming renderTarget is passed from elsewhere)
    if (renderTarget == nullptr) {
        std::cerr << "Failed to create render target." << std::endl;
        SDL_Quit();
        exit(1);
    }
}

void Init::init_fade(Fade* fade) {
    Collage collage;
    fade->Text::set_renderer(renderTarget);
    fade->init_text(collage.get_path(0), 24, {255, 0, 0}, 999, 999, 200, 90);
    fade->Body::set_surface(renderTarget);
    fade->set_texture(collage.get_path(1));
    fade->set_cords(999, 999);
}

void Init::init_pause(Pause* pause) {
    Collage collage;
    pause->Text::set_renderer(renderTarget);
    pause->init_text(collage.get_path(0), 24, {255, 0, 0}, 999, 999, 200, 90);
    pause->Body::set_surface(renderTarget);
    pause->set_texture(collage.get_path(1));
    pause->set_cords(999, 999);
}

void Init::init_clock(Clock* clock, Fade* fade, Overlay* overlay) {
    Collage collage;
    clock->Text::set_renderer(renderTarget);
    clock->init_text(collage.get_path(0), 24, {255, 0, 0}, 400, 330, 200, 90);
    clock->Body::set_surface(renderTarget);
    clock->set_texture(collage.get_path(9));
    clock->set_cords(400, 320);
}

void Init::init_overlay(Fade* fade, Clock* clock, Overlay* overlay) {
    overlay->init(fade, clock);
}

void Init::init_item_array(Item itemArray[], int itemAmount) {
    Collage collage;
    Item itemTemplate;
    itemTemplate.set_surface(renderTarget);
    itemTemplate.set_texture(collage.get_path(2));
    itemTemplate.set_cords(-100, -100);

    for (int i = 0; i < itemAmount; i++) {
        itemArray[i] = itemTemplate;
    }
}

void Init::init_tile_array(Tile tileArray[], int tileAmount) {
    Collage collage;
    Tile tileTemplate;
    tileTemplate.set_surface(renderTarget);
    tileTemplate.set_texture(collage.get_path(2));
    tileTemplate.set_cords(-100, -100);

    for (int i = 0; i < tileAmount; i++) {
        tileArray[i] = tileTemplate;
    }
}

void Init::init_map_array(Tile* tileArray, int tileAmount, Item* itemArray, int itemAmount, std::unique_ptr<Map>* mapArray, int mapAmount) {
    for (int i = 0; i < mapAmount; i++) {
        Map_Factory::Map_Type mapType = (i == 0) ? Map_Factory::Map_Type::Maze : (random.flip_coin() ? Map_Factory::Map_Type::Cage : Map_Factory::Map_Type::Garden);
        mapArray[i] = Map_Factory::createMap(mapType);
        mapArray[i]->set_tile_array(tileArray, tileAmount);
        mapArray[i]->set_item_array(itemArray, itemAmount);
        mapArray[i]->set_random_pointer(random);
        mapArray[i]->set_map_id(i);
        if (i == 0) {
            mapArray[i]->set_textures();
        }
    }
}

void Init::init_topography(std::unique_ptr<Map>* mapArray, int mapAmount, Topography* topography) {
    topography->set_renderer(renderTarget);
    Item* itemPtr = mapArray[0]->get_item_array();
    int itemAmount = mapArray[0]->get_item_size();
    Tile* tilePtr = mapArray[0]->get_tile_array();
    int tileAmount = mapArray[0]->get_tile_size();
    
    topography->set_map_array(mapArray, mapAmount);
    topography->set_item_array(itemPtr, itemAmount);
    topography->set_tile_array(tilePtr, itemAmount);
    topography->set_random_pointer(random);

    topography->set_up();
    topography->make_maze();

    for (int i = 1; i < mapAmount; i++) {
        if (topography->counter_maps == i) {
            std::cout << "END GENERATED!" << std::endl;
            break;
        }
        mapArray[i]->set_layout(topography->get_layout(i));
    }
    mapArray[0]->set_textures();
}

void Init::init_player_array(Acteur playerArray[], int playerAmount, Topography& topography) {
    Collage collage;
    for (int i = 0; i < playerAmount; i++) {
        Acteur player;
        player.set_controller_number(i);
        player.set_Topography(&topography);
        player.set_random_pointer(random);
        playerArray[i] = player;
    }

    playerArray[0].set_surface(renderTarget);
    playerArray[0].set_texture(collage.get_path(3));
    playerArray[0].set_cords_frames(32, 32, 3, 4);

    playerArray[1].set_surface(renderTarget);
    playerArray[1].set_texture(collage.get_path(4));
    playerArray[1].set_cords_frames(32, 32, 3, 4);

    playerArray[2].set_surface(renderTarget);
    playerArray[2].set_texture(collage.get_path(5));
    playerArray[2].set_cords_frames(400, 300, 3, 4);
}

void Init::init_entity(Acteur entityArray[], int entityAmount, Topography& topography) {
    Collage collage;
    
    for (int i = 0; i < entityAmount; i++) {
        Acteur entity;
        entity.set_controller_number(3 + i);
        entity.set_Topography(&topography);
        entity.set_random_pointer(random);
        entityArray[i] = entity;
    }

    entityArray[0].set_surface(renderTarget);
    entityArray[0].set_texture(collage.get_path(6));
    entityArray[0].set_cords_frames(4000, 4000, 1, 1);
}
