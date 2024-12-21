#pragma once

#include "../../../../core/Body.h"
#include "../../../Acteur.h"

#include "../tile_manager/Tile.h"
#include "../item_manager/Item.h"

#include "../../../../ui/Pause.h"
#include "../../../../ui/Fade.h"
#include "../../../../ui/Overlay.h"

#include "../../../../core/Clock.h"

#include "SDL.h"


class Game {
private:
    SDL_Renderer* renderTarget;
    SDL_Texture* texture;
    int levelWidth, levelHeight;

    Topography& topography;

    Acteur* player_array;
    int player_count;

    Acteur* entity;
    int entity_count;

    Item* item_array;
    int item_count;

    Tile* tile_array;
    int tile_count;
    
    Pause& pause;
    Clock& clock;
    Fade& fade;
    Overlay& overlay;

public:  
    Game(
        SDL_Renderer* renderer,
        SDL_Texture* tex, 
        Topography& topo, 
        Acteur* players,
        int playerCount,
        Acteur* entities,
        int entityCount,
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
