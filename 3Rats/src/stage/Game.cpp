#include "Game.h"

Game::~Game()
{
}
Game::Game(SDL_Renderer *renderer, SDL_Texture *tex, Topography &topo, ActeurManager &acteur_manager, Item *items, int itemCount, Tile *tiles, int tileCount, int lvlWidth, int lvlHeight, Pause &pauseObj, Clock &clockObj, Fade &fadeObj, Overlay &overlayObj): 
    renderTarget(renderer), texture(tex), topography(topo), item_array(items), tile_array(tiles), levelWidth(lvlWidth), levelHeight(lvlHeight), pause(pauseObj), clock(clockObj), 
    fade(fadeObj), overlay(overlayObj) 
    {
        this->acteur_manager = &acteur_manager;
    }
void Game::update(float delta, const Uint8 *keyState, int mode)
{
    //SDL_Log("[Game]: Update called ...");

    fade.update(std::to_string(clock.get_day()));
    pause.update("Pause.");
    clock.update(delta);
    acteur_manager->update_all(delta, keyState, mode, acteur_manager->get_players()[0]);
}

void Game::render() {
    //SDL_Log("[Game]: Draw called ...");

    SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
    SDL_RenderClear(renderTarget);
    SDL_RenderCopy(renderTarget, texture, NULL, NULL);

    fade.Fade::draw(renderTarget);
    pause.draw(renderTarget);
    clock.draw(renderTarget);

    for (int i = 0; i < Main_Constants::ITEM_AMOUNT; ++i) {
        item_array[i].draw(renderTarget);
    }
    for (int i = 0; i < Main_Constants::TILE_AMOUNT; ++i) {
        tile_array[i].draw(renderTarget);
    }

    acteur_manager->draw_all(renderTarget);
}
