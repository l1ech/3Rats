#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <memory>
#include "game/Item.h"
#include "game/Body.h"
#include "game/Map.h"
#include "game/Tile.h"
#include "game/Acteur.h"
#include "core/Clock.h"
#include "core/Random.h"
#include "ui/Fade.h"
#include "ui/Overlay.h"
#include "ui/Pause.h"
#include "core/Collage.h"
#include "game/Map_Factory.h"
#include "game/Topography.h"
#include "input_handler.h"  
#include "seed_manager.h"

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

#endif // INIT_H
