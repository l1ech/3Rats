#pragma once

#include <vector>
#include "../../Acteur.h"
#include "../../factory/acteur_factory/acteur_type/Player.h"
#include "../../../core/init.h"

class Init;  // Forward declaration of Init

class ActeurManager {
public:
    ActeurManager();
    ~ActeurManager();

    void update_all(float delta, const Uint8 *keyState, int mode, Player &front_rat);

    void draw_all(SDL_Renderer *renderTarget);

    void init(Init init, Topography* topography, Player p[], Player e[]);

    Player* get_players() { return players; }
    Player* get_entities() { return entities; }

    int get_player_count() { return Main_Constants::PLAYER_AMOUNT; }
    int get_entity_count() { return Main_Constants::ENTITY_AMOUNT; }

private:
    Player* players;
    Player* entities;
};
