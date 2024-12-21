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
    std::cout << "[Game]: Update called ..." << std::endl;
    fade.update(std::to_string(clock.get_day()));
    clock.update(delta);

    player_array[0].Update(delta, keyState, mode, player_array[2]);

    for (int i = 1; i < player_count; i++) {
        player_array[i].Update(delta, keyState, mode, player_array[i - 1]);
    }

    entity[0].update(delta);

    std::string pause_message = "Pause.";
    pause.update(pause_message);
    overlay.update(delta);
}

void Game::render() {
    std::cout << "[Game]: draw called ..." << std::endl;
    SDL_QueryTexture(texture, NULL, NULL, &levelWidth, &levelHeight);
    SDL_RenderClear(renderTarget);
    SDL_RenderCopy(renderTarget, texture, NULL, NULL);

    fade.Fade::draw(renderTarget);
    clock.draw(renderTarget);


    for (int i = 0; i < item_count; ++i) {
        item_array[i].draw(renderTarget);
    }
    for (int i = 0; i < tile_count; ++i) {
        tile_array[i].draw(renderTarget);
    }
    for (int i = 0; i < player_count; ++i) {
        player_array[i].draw(renderTarget);
    }

    entity[0].draw(renderTarget);
    pause.draw(renderTarget);
}