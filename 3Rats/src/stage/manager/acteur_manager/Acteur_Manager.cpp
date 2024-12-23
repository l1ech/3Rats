#include "Acteur_Manager.h"


ActeurManager::ActeurManager()
{
}

ActeurManager::~ActeurManager()
{
}

void ActeurManager::update_all(float delta, const Uint8 *keyState, int mode, Player &front_rat)
{
    players[0].Update(delta, keyState, mode, players[2]);

    for (int i = 1; i < Main_Constants::PLAYER_AMOUNT; i++) {
        players[i].Update(delta, keyState, mode, players[i - 1]);
    }

    for (int i = 0; i < Main_Constants::ENTITY_AMOUNT; i++) {
        entities[i].update(delta);
    }
}

void ActeurManager::draw_all(SDL_Renderer *renderTarget)
{
    for (int i = 0; i < Main_Constants::PLAYER_AMOUNT; ++i) {
        players[i].draw(renderTarget);
    }

    for (int i = 0; i < Main_Constants::ENTITY_AMOUNT; ++i) {
        entities[i].draw(renderTarget);
    }
}

void ActeurManager::init(Init init, Topography* topography, Player p[], Player e[])
{
    players = p;
    entities = e;

    init.init_player_array(p, *topography);
    init.init_entity(e, *topography);
}
