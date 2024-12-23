#pragma once
//#include <SDL.h>
#include <SDL2/SDL.h>

#include <memory>

#include "stage/handler/input_handler/input_handler.h"  

#include "stage/manager/clock_manager/Clock.h"
#include "stage/manager/clock_manager/Clock_Manager.h"

#include "stage/manager/item_manager/Item.h"

#include "stage/manager/tile_manager/Tile.h"

#include "stage/manager/game_manager/Game.h"

#include "stage/manager/acteur_manager/Acteur.h"
#include "stage/manager/acteur_manager/Acteur_Manager.h"
#include "stage/manager/acteur_manager/Player.h"

#include "stage/manager/seed_manager/seed_manager.h"

#include "stage/manager/map_manager/Topography.h"

#include "stage/factory/map_factory/Map_Factory.h"

#include "core/Body.h"
#include "core/Random.h"
#include "core/Constants.h"

#include "ui/Fade.h"
#include "ui/Overlay.h"
#include "ui/Pause.h"


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
    void init_clock(Clock* clock, Fade* fade, Overlay* overlay, Time* world_time);
    void init_overlay(Fade* fade, Clock* clock, Overlay* overlay);
    void init_item_array(Item itemArray[]);
    void init_tile_array(Tile tileArray[]);
    void init_map_array(Tile* tileArray, Item* itemArray, std::unique_ptr<Map>* mapArray);
    void init_topography(std::unique_ptr<Map>* mapArray, Topography* topography);
    void init_player_array(Player playerArray[], Topography& topography);
    void init_entity(Player entityArray[], Topography& topography);
};
