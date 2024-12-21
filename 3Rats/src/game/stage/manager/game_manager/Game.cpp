#include "Game.h"

Game::Game(
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
) : renderTarget(renderer), texture(tex), topography(topo), player_array(players), player_count(playerCount), 
    entity(entities), entity_count(entityCount), item_array(items), item_count(itemCount), tile_array(tiles), 
    tile_count(tileCount), levelWidth(lvlWidth), levelHeight(lvlHeight), pause(pauseObj), clock(clockObj), 
    fade(fadeObj), overlay(overlayObj) {}
    
Game::~Game()
{
}
void Game::update(float delta, const Uint8 *keyState, int mode)
{
    ActeurManager acteurManager;

    std::cout << "[Game]: Update called ..." << std::endl;
    fade.update(std::to_string(clock.get_day()));
    pause.update("Pause.");
    clock.update(delta);

    acteurManager.update(delta, keyState, mode, player_array[0], player_array, player_count, entity, entity_count);
}

void Game::render() {

    ActeurManager acteurManager;

    std::cout << "[Game]: draw called ..." << std::endl;
    SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
    SDL_RenderClear(renderTarget);
    SDL_RenderCopy(renderTarget, texture, NULL, NULL);

    fade.Fade::draw(renderTarget);
    pause.draw(renderTarget);
    clock.draw(renderTarget);

    for (int i = 0; i < item_count; ++i) {
        item_array[i].draw(renderTarget);
    }
    for (int i = 0; i < tile_count; ++i) {
        tile_array[i].draw(renderTarget);
    }

    acteurManager.draw(renderTarget, player_array, player_count, entity, entity_count);
}