// Prologue.cpp
#include "Prologue.h"
#include <iostream>

Prologue::Prologue(SDL_Renderer* renderer, Stage& stage, Random& random)
    : renderTarget(renderer), stage(stage), random(random), mapArray(nullptr), mapAmount(0) {}

bool Prologue::Initialize() {
    // Initialize SDL components or other prologue-related tasks
    return true; // Return true if successful, false otherwise
}

void Prologue::InitEntityArray(Acteur entityArray[], int entityAmount, Map* map, int map_size) {
    for (int i = 0; i < entityAmount; i++) {
        Acteur entity;
        entity.set_controller_number(controller_number++);
        //entity.set_Stage(&stage);
        entity.set_random_pointer(random);
        entityArray[i] = entity;
    }

    if (entityAmount > 0) {
        entityArray[0].set_renderer(renderTarget);
        entityArray[0].set_texture("npc_textures/entity.png");
        entityArray[0].set_cords_frames(100, 100, 3, 4);
        entityArray[0].set_map_array(map, map_size);
    }
}

void Prologue::InitPlayerArray(Acteur playerArray[], int playerAmount, Map* map, int map_size) {
    for (int i = 0; i < playerAmount; i++) {
        Acteur player;
        player.set_controller_number(controller_number++);
        //player.set_Stage(&stage);
        player.set_random_pointer(random);
        playerArray[i] = player;
    }

    if (playerAmount > 0) {
        playerArray[0].set_renderer(renderTarget);
        playerArray[0].set_texture("rat_textures/mango.png");
        playerArray[0].set_cords_frames(32, 32, 3, 4);
        playerArray[0].set_role(0);
        playerArray[0].set_map_array(map, map_size);
    }
    if (playerAmount > 1) {
        playerArray[1].set_renderer(renderTarget);
        playerArray[1].set_texture("rat_textures/fridolin.png");
        playerArray[1].set_cords_frames(32, 32, 3, 4);
        playerArray[1].set_role(1);
        playerArray[1].set_map_array(map, map_size);

    }
    if (playerAmount > 2) {
        playerArray[2].set_renderer(renderTarget);
        playerArray[2].set_texture("rat_textures/remy.png");
        playerArray[2].set_cords_frames(400, 300, 3, 4);
        playerArray[2].set_role(1);
        playerArray[2].set_map_array(map, map_size);

    }
}

void Prologue::InitStage(Map mapArray[], int mapAmount, Acteur* player_array, int player_amount, Acteur* entity_array, int entity_amount, Chest* chest) {
    this->mapArray = mapArray;
    this->mapAmount = mapAmount;

    init_stage
    (
        renderTarget, mapArray, 
        mapAmount, &stage, random, 
        player_array, player_amount, 
        entity_array, entity_amount, 
        chest);
}

void Prologue::InitProps(Prop propArray[], int propAmount) {
    Prop propTemplate;
    propTemplate.set_renderer(renderTarget);
    propTemplate.set_texture("meta_textures/place_holder.png");
    propTemplate.set_cords(-100, -100);

    for (int i = 0; i < propAmount; i++) {
        propArray[i] = propTemplate;
    }
}

void Prologue::InitTiles(Tile tileArray[], int tileAmount) {
    Tile tileTemplate;
    tileTemplate.set_renderer(renderTarget);
    tileTemplate.set_texture("meta_textures/place_holder.png");
    tileTemplate.set_cords(-100, -100);

    for (int i = 0; i < tileAmount; i++) {
        tileArray[i] = tileTemplate;
    }
}

void Prologue::InitGameObjects(Fade* fade, Scene* scene, Clock* clock, Pause* pause, Button* button, Sound* sound, Acteur* player_array, int player_amount) {
    // Initialize Fade
    fade->Text::set_renderer(renderTarget);
    fade->Text::init("fonts/sans.ttf", 24, { 255, 0, 0 }, 999, 999, 200, 90);
    fade->Body::set_renderer(renderTarget);
    fade->Body::set_texture("ui_textures/fade.png");
    fade->Body::set_cords(999, 999);

    // Initialize Curtain
    scene->init(fade, clock, button, pause);
    scene->set_sound(sound);
    scene->set_player_array(player_array, player_amount);

    // Initialize Clock
    clock->Text::set_renderer(renderTarget);
    clock->Text::init("fonts/sans.ttf", 24, { 255, 0, 0 }, 400, 330, 200, 90);
    clock->Body::set_renderer(renderTarget);
    clock->set_texture("ui_textures/clock_frame.png");
    clock->set_cords(400, 320);
    clock->set_time(16, 30);

    // Initialize Pause
    pause->Text::set_renderer(renderTarget);
    pause->Text::init("fonts/sans.ttf", 24, { 255, 0, 0 }, 999, 999, 200, 90);
    pause->Body::set_renderer(renderTarget);
    pause->Body::set_texture("ui_textures/fade.png");
    pause->Body::set_cords(999, 999);
    pause->set_button(button);

    // Initialize Sound
    sound->init();
}

void Prologue::init_stage(SDL_Renderer* renderTarget, Map* map_ptr, int map_amount, Stage* stage, Random& random, Acteur* player_array, int player_amount, Acteur* entity_array, int entity_amount, Chest* chest)
{
    stage->set_renderer(renderTarget);

    Prop* prop_ptr = map_ptr[0].get_prop_array();
    int prop_amount = map_ptr[0].get_prop_size();

    Tile* tile_ptr = map_ptr[0].get_tile_array();
    int tile_amount = map_ptr[0].get_tile_size();

    stage->set_map_array(map_ptr, map_amount);
    stage->set_player_array(player_array, player_amount);
    stage->set_entity_array(entity_array, entity_amount);
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


    // Initialize Chest
    chest->re_size(4);
    chest->set_renderer(renderTarget);
    chest->set_texture("prop_textures/chest/chest.png");
    chest->set_cords_frames(64, 64, 1, 4);
}

void Prologue::InitMapArray(Tile* tileArray, int tileAmount, Prop* propArray, int propAmount, Map* mapArray, int mapAmount)
{
    Map mapTemplate;

    mapTemplate.set_tile_array(tileArray, tileAmount);
    init_grid_coords(tileArray, tileAmount, mapTemplate.get_hight(), mapTemplate.get_width());
    mapTemplate.set_prop_array(propArray, propAmount);
    init_grid_coords(propArray, propAmount, mapTemplate.get_hight(), mapTemplate.get_width());
    mapTemplate.set_random_pointer(random);

    for (int i = 0; i < mapAmount; i++) {
        mapArray[i] = mapTemplate;
        mapArray[i].set_map_id(i);
    }
}

void Prologue::init_game(Tile* tile_array, int tile_amount, Prop* prop_array, int prop_amount, Map* map_array, int map_amount, Acteur* entity_array, int entity_amount, Acteur* player_array, int player_amount, Chest* chest)
{
    controller_number = 0;

    InitProps(prop_array, prop_amount);

    InitTiles(tile_array, tile_amount);

    InitMapArray(tile_array, tile_amount, prop_array, prop_amount, map_array, map_amount);

    InitStage(map_array, map_amount, player_array, player_amount, entity_array, entity_amount, chest);

    InitPlayerArray(player_array, player_amount, mapArray, mapAmount);

    InitEntityArray(entity_array, entity_amount, mapArray, mapAmount);

}
