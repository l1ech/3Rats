#pragma once
#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL_log.h>

#include <fstream>
#include <memory>

#include "../stage/handler/input_handler/input_handler.h"  

#include "../stage/manager/clock_manager/Clock_Manager.h"
#include "../stage/manager/acteur_manager/Acteur_Manager.h"
#include "../stage/manager/seed_manager/seed_manager.h"
#include "../stage/manager/map_manager/Topography.h"

#include "../stage/factory/acteur_factory/acteur_type/Player.h"
#include "../stage/factory/map_factory/Map_Factory.h"

#include "../stage/Clock.h"
#include "../stage/Item.h"
#include "../stage/Tile.h"
#include "../stage/Game.h"
#include "../stage/Acteur.h"

#include "Body.h"
#include "Random.h"
#include "Constants.h"
#include "Logger.h"
#include "utils.h"  

#include "../ui/Fade.h"
#include "../ui/Overlay.h"
#include "../ui/Pause.h"


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
