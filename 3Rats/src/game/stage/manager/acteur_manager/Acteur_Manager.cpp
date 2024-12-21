#include "Acteur_Manager.h"

ActeurManager::ActeurManager()
{
}

ActeurManager::~ActeurManager()
{
}

void ActeurManager::update(float delta, const Uint8 *keyState, int mode, Acteur &front_rat, Acteur *acteurs, int max_acteurs, Acteur *entitys, int max_entity)
{
    acteurs[0].Update(delta, keyState, mode, acteurs[2]);

    for (int i = 1; i < max_acteurs; i++) {
        acteurs[i].Update(delta, keyState, mode, acteurs[i - 1]);
    }

    entitys[0].update(delta);

}

void ActeurManager::draw(SDL_Renderer *renderTarget, Acteur* acteurs, int max_acteurs, Acteur* entitys, int max_entitys)
{
    for (int i = 0; i < max_acteurs; ++i) {
        acteurs[i].draw(renderTarget);
    }

    entitys[0].draw(renderTarget);
}