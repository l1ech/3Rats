#include "init.h"
#include <SDL_log.h>

Init::Init(SDL_Renderer* renderTarget, Random& random, uint32_t seed, int screenWidth, int screenHeight)
    : renderTarget(renderTarget), random(random), seed(seed), screenWidth(screenWidth), screenHeight(screenHeight) 
{

    if (renderTarget == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Init]: Renderer is null!");
    } else {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: Renderer initialized successfully.");
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: Initialization of Init class completed.");
}

void Init::init_fade(Fade* fade) {
    fade->set_name("fade");
    fade->set_surface(renderTarget); 
    fade->init_text(
        Texture_Constants::FONT, 
        Init_Constants::TEXT_SIZE, 
        Init_Constants::TEXT_COLOR, 
        Init_Constants::FADE_TEXT_X, 
        Init_Constants::FADE_TEXT_Y, 
        Init_Constants::FADE_WIDTH, 
        Init_Constants::FADE_HEIGHT
    );
    fade->set_texture_path(Texture_Constants::UI_TEXTURE);
    fade->set_cords(
        Init_Constants::FADE_X, 
        Init_Constants::FADE_Y
    );

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: Fade initialized with texture and coordinates.");
}


void Init::init_pause(Pause* pause) {
    //Texture_Manager texture_manager;
    pause->set_name("pause");
    pause->set_surface(renderTarget);

    //pause->Text::set_renderer(renderTarget);
    pause->init_text(
        Texture_Constants::FONT, 
        Init_Constants::TEXT_SIZE, 
        Init_Constants::TEXT_COLOR, 
        Init_Constants::FADE_TEXT_X, 
        Init_Constants::FADE_TEXT_Y, 
        Init_Constants::FADE_WIDTH, 
        Init_Constants::FADE_HEIGHT
    );
    //pause->Body::set_surface(renderTarget);
    pause->set_texture_path(Texture_Constants::UI_TEXTURE);
    pause->set_cords(
        Init_Constants::FADE_TEXT_X, 
        Init_Constants::FADE_TEXT_Y
    );

    //pause->set_hight(Init_Constants::FADE_HEIGHT);
    //pause->set_width(Init_Constants::FADE_WIDTH);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Init]: Pause initialized with texture and coordinates.");
}
void Init::init_clock(Clock* clock, Fade* fade, Overlay* overlay, Time* world_time) {
    // Initialize the base classes just like you do in the other functions

    clock->set_renderer(renderTarget);    

    clock->set_name("clock");
    clock->set_timer(*world_time);  // Make sure world_time is correctly initialized
    clock->init_text(
        Texture_Constants::FONT, 
        Init_Constants::TEXT_SIZE, Init_Constants::TEXT_COLOR, 
        Init_Constants::CLOCK_X, Init_Constants::CLOCK_Y, 
        Init_Constants::CLOCK_WIDTH, Init_Constants::CLOCK_HEIGHT
    );
    clock->set_texture_path(Texture_Constants::CLOCK_FRAME);
    clock->set_cords(
        Init_Constants::CLOCK_X, Init_Constants::CLOCK_Y
    );

    SDL_Log("[init]: Clock initialized with texture and coordinates.");
}


void Init::init_overlay(Fade* fade, Clock* clock, Overlay* overlay) {
    overlay->init(fade, clock);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[init]: Overlay initialized with fade and clock.");    
}
void Init::init_item_array(Item itemArray[])
{
    if (itemArray == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[init]: Error - itemArray is null!");
        return;
    }

    if (renderTarget == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[init]: Error - renderTarget is null!");
        return;
    }

    for (int i = 0; i < Main_Constants::ITEM_AMOUNT; i++) {
        Item itemTemplate;
        itemTemplate.set_name("item<" + std::to_string(i) + ">");
        itemTemplate.set_surface(renderTarget); // Set renderer

        // Handle texture setting with more detailed logging for debugging
        switch (i % Init_Constants::NUM_TEXTURES) {
            case 0:
                itemTemplate.set_texture_path(Texture_Constants::META_TEXTURE);
                break;
            case 1:
                itemTemplate.set_texture_path(Texture_Constants::META_TEXTURE);
                break;
            case 2:
                itemTemplate.set_texture_path(Texture_Constants::META_TEXTURE);
                break;
            default:
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[init]: Invalid texture index.");
                return;
        }

        itemTemplate.set_cords(Init_Constants::ITEM_INITIAL_X + (i * Init_Constants::OFFSET_X), Init_Constants::ITEM_INITIAL_Y + (i * Init_Constants::OFFSET_Y));
        itemArray[i] = itemTemplate;

        SDL_Log("[init]: Initialized item %d with texture and coordinates.", i);
    }
    SDL_Log("[init]: Item array initialized with %d items.", Main_Constants::ITEM_AMOUNT);
}

void Init::init_tile_array(Tile tileArray[]) {
    if (tileArray == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[init]: Error - tileArray is null!");
        return;
    }

    for (int i = 0; i < Main_Constants::TILE_AMOUNT; i++) {
        Tile tileTemplate;
        tileTemplate.set_name("tile<" + std::to_string(i) + ">");
        tileTemplate.set_surface(renderTarget); // Set renderer
        //tileTemplate.set_texture_path(Texture_Constants::META_TEXTURE); // Set texture
        tileTemplate.set_cords(Init_Constants::TILE_INITIAL_X, Init_Constants::TILE_INITIAL_Y);
        tileArray[i] =  tileTemplate;
        SDL_Log("[init]: Initialized tile <%d> with texture and coordinates.", i);
    }
    SDL_Log("[init]: Tile array initialized with %d tiles.", Main_Constants::TILE_AMOUNT);
}
void Init::init_map_array(Tile* tileArray, Item* itemArray, std::unique_ptr<Map>* mapArray) {
    for (int i = 0; i < Main_Constants::MAP_AMOUNT; i++) {
        Map_Constants::Map_Type mapType = Map_Constants::Map_Type::Cage;
        mapArray[i] = Map_Factory::createMap(mapType);
        mapArray[i]->set_random_ptr(&random);
        mapArray[i]->generate(false, false);
        // TODO: remove this, these infos are in game
        mapArray[i]->set_tile_array(tileArray, Main_Constants::TILE_AMOUNT);
        mapArray[i]->set_item_array(itemArray, Main_Constants::ITEM_AMOUNT);

        mapArray[i]->set_random_pointer(random);
        mapArray[i]->set_map_id(i);
    }
    SDL_Log("[init]: Map array initialized with %d maps.", Main_Constants::MAP_AMOUNT);
}

void Init::init_topography(std::unique_ptr<Map>* mapArray, Topography* topography) {

    topography->set_renderer(renderTarget);
    Item* itemPtr = mapArray[0]->get_item_array();
    Tile* tilePtr = mapArray[0]->get_tile_array();

    topography->set_map_array(mapArray, Main_Constants::MAP_AMOUNT);
    topography->set_item_array(itemPtr, Main_Constants::ITEM_AMOUNT);
    topography->set_tile_array(tilePtr, Main_Constants::TILE_AMOUNT);
    topography->set_random_pointer(random);

    for (int i = 0; i < Main_Constants::MAP_AMOUNT; i++) {
        topography->set_up(mapArray[i].get());
    }
    
    topography->make_maze();

    for (int i = 0; i < Main_Constants::MAP_AMOUNT; i++) {
        if (topography->counter_maps == i) {
            SDL_Log("[init]: maze-end generated ");
            break;
        }
        //mapArray[i]->set_layout(topography->get_layout(i));
    }

    //generate_map(topography, mapArray[0].get());
    //tm.set_textures(tilePtr, topography->get_map_data(), Main_Constants::TILE_AMOUNT, renderTarget);
    //mapArray[0]->set_textures();

    SDL_Log("[init]: Topography initialized and maze generated.");
}

void Init::init_player_array(Player playerArray[], Topography& topography) {

    for (int i = 0; i < Main_Constants::PLAYER_AMOUNT; i++) {
        Player player;
        player.set_name("player<" + std::to_string(i) + ">");
        player.set_controller_number(i);
        player.set_Topography(&topography);
        player.set_random_pointer(random);
        player.set_surface(renderTarget);
        player.set_texture_path(Texture_Constants::META_TEXTURE);
        playerArray[i] = player;
    }

    playerArray[0].set_texture_path(Texture_Constants::RAT_TEXTURE_MANGO);
    playerArray[0].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );


    playerArray[1].set_texture_path(Texture_Constants::RAT_TEXTURE_FRIDOLIN);
    playerArray[1].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );

    playerArray[2].set_texture_path(Texture_Constants::RAT_TEXTURE_REMY);
    playerArray[2].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );

    SDL_Log("[init]: Player array initialized with size: %d", Main_Constants::PLAYER_AMOUNT);
}

void Init::init_entity(Player entityArray[], Topography& topography) {
    for (int i = 0; i < Main_Constants::ENTITY_AMOUNT; i++) {
        Player entity;
        entity.set_controller_number(3 + i);
        entity.set_Topography(&topography);
        entity.set_random_pointer(random);
        entity.set_name("entity<" + std::to_string(i) + ">");
        entity.set_surface(renderTarget);
        entity.set_texture_path(Texture_Constants::META_TEXTURE);
        entityArray[i] = entity;
    }

    entityArray[0].set_surface(renderTarget);
    entityArray[0].set_texture_path(Texture_Constants::NPC_TEXTURE);
    entityArray[0].set_cords_frames(
        Init_Constants::ENTITY_INITIAL_X, Init_Constants::ENTITY_INITIAL_Y, Init_Constants::ENTITY_FRAME_ROWS, Init_Constants::ENTITY_FRAME_COLUMNS
    );
    SDL_Log("[init]: Entity array initialized with %d entities.", Main_Constants::ENTITY_AMOUNT);
}