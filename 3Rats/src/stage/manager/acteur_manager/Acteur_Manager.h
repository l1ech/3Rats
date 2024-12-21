#pragma once

#include <vector>
#include "Acteur.h"
#include "../../../init.h"

class Init;  // Forward declaration of Init

class ActeurManager {
public:
    ActeurManager();
    ~ActeurManager();

    void update(float delta, const Uint8 *keyState, int mode, Acteur &front_rat, Acteur *acteurs, int max_acteurs, Acteur *entity, int max_entity);

    void draw(SDL_Renderer *renderTarget, Acteur* acteurs, int max_acteurs, Acteur* entitys, int max_entitys);

    void init(Init init, Topography* topography, Acteur* player_array, Acteur* entity_array);

    Acteur* get_players() { return players; }
    Acteur* get_entities() { return entities; }

private:
    Acteur* players;
    Acteur* entities;
};
