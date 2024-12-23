#pragma once

#include "../../../core/Body.h"

#include "../acteur_manager/Acteur.h"
#include "../acteur_manager/Acteur_Manager.h"
#include "../tile_manager/Tile.h"
#include "../item_manager/Item.h"
#include "../clock_manager/Clock.h"


#include "../../../ui/Pause.h"
#include "../../../ui/Fade.h"
#include "../../../ui/Overlay.h"


#include "SDL2/SDL.h"

class ActeurManager;

class Game {
private:
    SDL_Renderer* renderTarget;
    SDL_Texture* texture;
    int levelWidth, levelHeight;

    Topography& topography;

    //Player* players;
    //int player_count;

    //Player* entity;
    //int entity_count;

    Item* item_array;
    //int item_count;

    Tile* tile_array;
    //int tile_count;
    
    Pause& pause;
    Clock& clock;
    Fade& fade;
    Overlay& overlay;

public:  

    ActeurManager* acteur_manager;

    Game(
        SDL_Renderer* renderer,
        SDL_Texture* tex, 
        Topography& topo, 
        ActeurManager& acteur_manager,
        Item* items, 
        int itemCount,
        Tile* tiles,
        int tileCount,
        int lvlWidth,
        int lvlHeight,
        Pause& pauseObj, 
        Clock& clockObj, 
        Fade& fadeObj, 
        Overlay& overlayObj
    );

    ~Game(); // Add destructor
    void update(float delta, const Uint8 *keyState, int mode);
    void render();
};
