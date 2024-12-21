#pragma once

#include <SDL.h>
#include <memory>

#include "../stage/manager/item_manager/Item.h"
#include "../stage/manager/tile_manager/Tile.h"
#include "../stage/manager/game_manager/Game.h"
#include "../stage/manager/acteur_manager/Acteur.h"
#include "../stage/manager/acteur_manager/Acteur_Manager.h"
#include "../stage/manager/map_manager/Topography.h"
#include "../stage/factory/map_factory/Map_Factory.h"

#include "Body.h"
#include "Clock.h"
#include "Random.h"
#include "input_handler.h"  
#include "seed_manager.h"

#include "../ui/Fade.h"
#include "../ui/Overlay.h"
#include "../ui/Pause.h"

#include "Constants.h"

class Init {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderTarget = nullptr;
    Random random;

    int screenWidth;
    int screenHeight;
    int seed;

public:
    Init(SDL_Renderer* render_target, Random& random, uint32_t seed, int screenWidth, int screenHeight);
    
    void init_fade(Fade* fade);
    void init_pause(Pause* pause);
    void init_clock(Clock* clock, Fade* fade, Overlay* overlay);
    void init_overlay(Fade* fade, Clock* clock, Overlay* overlay);
    void init_item_array(Item itemArray[], int itemAmount);
    void init_tile_array(Tile tileArray[], int tileAmount);
    void init_map_array(Tile* tileArray, int tileAmount, Item* itemArray, int itemAmount, std::unique_ptr<Map>* mapArray, int mapAmount);
    void init_topography(std::unique_ptr<Map>* mapArray, int mapAmount, Topography* topography);
    void init_player_array(Acteur playerArray[], int playerAmount, Topography& topography);
    void init_entity(Acteur entityArray[], int entityAmount, Topography& topography);
};
