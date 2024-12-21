#pragma once

#include <vector>
#include "Acteur.h"

class ActeurManager {
public:
    ActeurManager();
    ~ActeurManager();

    void update(float delta, const Uint8 *keyState, int mode, Acteur &front_rat, Acteur *acteurs, int max_acteurs, Acteur *entity, int max_entity);

    void draw(SDL_Renderer *renderTarget, Acteur* acteurs, int max_acteurs, Acteur* entitys, int max_entitys);

private:

};
