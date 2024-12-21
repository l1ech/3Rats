#include "init.h"

Init::Init(SDL_Renderer* renderTarget, Random& random, uint32_t seed, int screenWidth, int screenHeight)
    : renderTarget(renderTarget), random(random), seed(seed), screenWidth(screenWidth), screenHeight(screenHeight)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "[Init]: SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "[Init]: SDL initialized successfully." << std::endl;
    }

    if (TTF_Init() < 0) {
        std::cerr << "[Init]: SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        std::cout << "[Init]: SDL_ttf initialized successfully." << std::endl;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG; // Adjust for supported image formats
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "[Init]: SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        std::cout << "[Init]: SDL_image initialized successfully." << std::endl;
    }

    if (renderTarget == nullptr) {
        std::cerr << "[Init]: Renderer is null!" << std::endl;
    } else {
        std::cout << "[Init]: Renderer initialized successfully." << std::endl;
    }

    std::cout << "[init]: Initialization of Init class completed." << std::endl;
}

void Init::init_fade(Fade* fade) {
    //Texture_Manager texture_manager;
    fade->set_name("fade");
    fade->Text::set_renderer(renderTarget);
    fade->Body::set_surface(renderTarget);

    fade->init_text (
            Texture_Constants::FONT, 
            Init_Constants::TEXT_SIZE, 
            Init_Constants::TEXT_COLOR, 
            Init_Constants::FADE_TEXT_X, 
            Init_Constants::FADE_TEXT_Y, 
            Init_Constants::FADE_WIDTH, 
            Init_Constants::FADE_HEIGHT
        );
    fade->set_texture(Texture_Constants::UI_TEXTURE);
    fade->set_cords(
        Init_Constants::FADE_X, 
        Init_Constants::FADE_Y
    );
    
    std::cout << "[init]: Fade initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_pause(Pause* pause) {
    //Texture_Manager texture_manager;
    pause->set_name("pause");
    pause->Text::set_renderer(renderTarget);
    pause->init_text(
        Texture_Constants::FONT, 
        Init_Constants::TEXT_SIZE, 
        Init_Constants::TEXT_COLOR, 
        Init_Constants::FADE_TEXT_X, 
        Init_Constants::FADE_TEXT_Y, 
        Init_Constants::FADE_WIDTH, 
        Init_Constants::FADE_HEIGHT
    );
    pause->Body::set_surface(renderTarget);
    pause->set_texture(Texture_Constants::UI_TEXTURE);
    pause->set_cords(
        Init_Constants::FADE_TEXT_X, 
        Init_Constants::FADE_TEXT_Y
    );

    std::cout << "[init]: Pause initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_clock(Clock* clock, Fade* fade, Overlay* overlay) {
    //Texture_Manager texture_manager;
    clock->set_name("clock");
    clock->Text::set_renderer(renderTarget);
    clock->init_text(
        Texture_Constants::FONT, 
        Init_Constants::TEXT_SIZE, 
        Init_Constants::TEXT_COLOR, 
        Init_Constants::CLOCK_X, 
        Init_Constants::CLOCK_Y, 
        Init_Constants::CLOCK_WIDTH, 
        Init_Constants::CLOCK_HEIGHT
    );
    clock->Body::set_surface(renderTarget);
    clock->set_texture(Texture_Constants::CLOCK_FRAME);
    clock->set_cords(
        Init_Constants::CLOCK_X, 
        Init_Constants::CLOCK_Y
    );

    std::cout << "[init]: Clock initialized with texture and coordinates." << std::endl;
    std::cout << std::endl;
}

void Init::init_overlay(Fade* fade, Clock* clock, Overlay* overlay) {
    overlay->init(fade, clock);
    std::cout << "[init]: Overlay initialized with fade and clock." << std::endl;
    std::cout << std::endl;
}
void Init::init_item_array(Item* itemArray, int itemAmount) {
    if (itemArray == nullptr) {
        std::cerr << "[init]: Error - itemArray is null!" << std::endl;
        return;
    }

    if (itemAmount > Init_Constants::MAX_ITEMS) {
        std::cerr << "[init]: Warning - itemAmount exceeds maximum (" << Init_Constants::MAX_ITEMS << ")." << std::endl;
        itemAmount = Init_Constants::MAX_ITEMS;
    }

    for (int i = 0; i < itemAmount; i++) {
        Item itemTemplate;
        itemTemplate.set_name("item<" + std::to_string(i) + ">");
        itemTemplate.set_surface(renderTarget); // Set renderer

        //itemTemplate.set_texture(texture_manager.get_path(i % Init_Constants::NUM_TEXTURES)); // Varied texture

        switch (i % Init_Constants::NUM_TEXTURES) {
            case 0:
                itemTemplate.set_texture(Texture_Constants::META_TEXTURE);
                break;
            case 1:
                itemTemplate.set_texture(Texture_Constants::META_TEXTURE);
                break;
            case 2:
                itemTemplate.set_texture(Texture_Constants::META_TEXTURE);
                break;
        }
        
        itemTemplate.set_cords(Init_Constants::ITEM_INITIAL_X + (i * Init_Constants::OFFSET_X), Init_Constants::ITEM_INITIAL_Y + (i * Init_Constants::OFFSET_Y));
        itemArray[i] = itemTemplate;

        std::cout << "[init]: Initialized item " << i << " with texture and coordinates." << std::endl;
    }
    std::cout << "[init]: Item array initialized with " << itemAmount << " items." << std::endl;
    std::cout << std::endl;
}

void Init::init_tile_array(Tile tileArray[], int tileAmount) {
    if (tileArray == nullptr) {
        std::cerr << "[init]: Error - tileArray is null!" << std::endl;
        return;
    }

    for (int i = 0; i < tileAmount; i++) {
        Tile tileTemplate;
        tileTemplate.set_name("tile");
        tileTemplate.set_surface(renderTarget); // Set renderer
        tileTemplate.set_texture(Texture_Constants::META_TEXTURE); // Set texture
        tileTemplate.set_cords(Init_Constants::TILE_INITIAL_X, Init_Constants::TILE_INITIAL_Y);
        tileArray[i] =  tileTemplate;
        std::cout << "[init]: Initialized tile " << i << " with texture and coordinates." << std::endl;
    }
    std::cout << "[init]: Tile array initialized with " << tileAmount << " tiles." << std::endl;
    std::cout << std::endl;
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

    for (int i = 0; i < mapAmount; i++) 
    {
        topography->set_up(mapArray[i].get());
    }
    
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
    for (int i = 0; i < playerAmount; i++) {
        Acteur player;
        player.set_name("player");
        player.set_controller_number(i);
        player.set_Topography(&topography);
        player.set_random_pointer(random);
        player.set_surface(renderTarget);
        player.set_texture(Texture_Constants::META_TEXTURE);
        playerArray[i] = player;
    }

    playerArray[0].set_texture(Texture_Constants::RAT_TEXTURE_MANGO);
    playerArray[0].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );


    playerArray[1].set_texture(Texture_Constants::RAT_TEXTURE_FRIDOLIN);
    playerArray[1].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );

    playerArray[2].set_texture(Texture_Constants::RAT_TEXTURE_REMY);
    playerArray[2].set_cords_frames(
        Init_Constants::PLAYER_FRAME_WIDTH, 
        Init_Constants::PLAYER_FRAME_HEIGHT, 
        Init_Constants::PLAYER_FRAME_ROWS, 
        Init_Constants::PLAYER_FRAME_COLUMNS
    );

    std::cout << "[init]: Player array initialized with " << playerAmount << "[init]:  players." << std::endl;
    std::cout << std::endl;
}

void Init::init_entity(Acteur entityArray[], int entityAmount, Topography& topography) {
    for (int i = 0; i < entityAmount; i++) {
        Acteur entity;
        entity.set_controller_number(3 + i);
        entity.set_Topography(&topography);
        entity.set_random_pointer(random);
        entity.set_name("entity");
        entity.set_surface(renderTarget);
        entity.set_texture(Texture_Constants::META_TEXTURE);
        entityArray[i] = entity;
    }

    entityArray[0].set_surface(renderTarget);
    entityArray[0].set_texture(Texture_Constants::NPC_TEXTURE);
    entityArray[0].set_cords_frames(Init_Constants::ENTITY_INITIAL_X, Init_Constants::ENTITY_INITIAL_Y, Init_Constants::ENTITY_FRAME_ROWS, Init_Constants::ENTITY_FRAME_COLUMNS);

    std::cout << "[init]: Entity array initialized with " << entityAmount << " entities." << std::endl;
    std::cout << std::endl;
}