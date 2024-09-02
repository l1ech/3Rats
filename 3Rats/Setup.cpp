
// Setup.cpp
#include "Setup.h"
#include <iostream>

Setup::Setup(SDL_Renderer* renderer, Stage& stage, Random& random)
    : renderTarget(renderer), stage(stage), random(random), mapArray(nullptr), mapAmount(0) {}

bool Setup::Initialize() {
    // Initialize SDL components or other setup-related tasks
    return true; // Return true if successful, false otherwise
}

void Setup::InitEntityArray(Acteur entityArray[], int entityAmount, int& controllerNum) {
    for (int i = 0; i < entityAmount; i++) {
        Acteur entity;
        entity.set_controller_number(controllerNum++);
        entity.set_Stage(&stage);
        entity.set_random_pointer(random);
        entityArray[i] = entity;
    }

    if (entityAmount > 0) {
        entityArray[0].set_renderer(renderTarget);
        entityArray[0].set_texture("npc_textures/entity.png");
        entityArray[0].set_cords_frames(100, 100, 3, 4);
    }
}

void Setup::InitPlayerArray(Acteur playerArray[], int playerAmount, int& controllerNum) {
    for (int i = 0; i < playerAmount; i++) {
        Acteur player;
        player.set_controller_number(controllerNum++);
        player.set_Stage(&stage);
        player.set_random_pointer(random);
        playerArray[i] = player;
    }

    if (playerAmount > 0) {
        playerArray[0].set_renderer(renderTarget);
        playerArray[0].set_texture("rat_textures/mango.png");
        playerArray[0].set_cords_frames(32, 32, 3, 4);
    }
    if (playerAmount > 1) {
        playerArray[1].set_renderer(renderTarget);
        playerArray[1].set_texture("rat_textures/fridolin.png");
        playerArray[1].set_cords_frames(32, 32, 3, 4);
    }
    if (playerAmount > 2) {
        playerArray[2].set_renderer(renderTarget);
        playerArray[2].set_texture("rat_textures/remy.png");
        playerArray[2].set_cords_frames(400, 300, 3, 4);
    }
}

void Setup::InitStage(Map mapArray[], int mapAmount) {
    this->mapArray = mapArray;
    this->mapAmount = mapAmount;

    Stage* stagePtr = &stage;
    init_stage(renderTarget, mapArray, mapAmount, stagePtr, random);
}

void Setup::init_stage(SDL_Renderer* renderTarget, Map* map_ptr, int map_amount, Stage* stage, Random& random)
{
    stage->set_renderer(renderTarget);

    Item* item_ptr = map_ptr[0].get_item_array();
    int item_amount = map_ptr[0].get_item_size();

    Tile* tile_ptr = map_ptr[0].get_tile_array();
    int tile_amount = map_ptr[0].get_tile_size();

    stage->set_map_array(map_ptr, map_amount);
    stage->set_random_pointer(random);

    stage->set_up();
    stage->make_maze();

    map_ptr[0].set_type(2);

    for (int i = 1; i < map_amount; i++)
    {
        if (stage->counter_maps == i)
        {
            std::cout << "END GENERATED!" << std::endl;
            break;
        }
        map_ptr[i].set_layout(stage->get_layout(i));
        map_ptr[i].set_type(random.flip_coin());
    }
    map_ptr[0].set_textures();
}