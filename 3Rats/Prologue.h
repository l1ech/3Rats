// Prologue.h
#pragma once
#include <SDL.h>
#include "Acteur.h"
#include "Stage.h"
#include "Random.h"
#include "Map.h"
#include "Prop.h"
#include "Tile.h"
#include "Fade.h"
#include "Curtain.h"
#include "Pause.h"
#include "Button.h"
#include "Sound.h"
#include "Chest.h"
#include "Clock.h"
#include "Scene.h"

class Prologue {
public:
    Prologue(SDL_Renderer* renderer, Stage& stage, Random& random);
    bool Initialize();
    void InitEntityArray(Acteur entityArray[], int entityAmount, Map* map, int map_size);
    void InitPlayerArray(Acteur playerArray[], int playerAmount, Map* map, int map_size);
    void InitStage(Map mapArray[], int mapAmount, Acteur* player_array, int player_amount, Acteur* entity_array, int entity_amount, Chest* chest);
    void InitProps(Prop propArray[], int propAmount);
    void InitTiles(Tile tileArray[], int tileAmount);
    void InitGameObjects(Fade* fade, Scene* scene, Clock* clock, Pause* pause, Button* button, Sound* sound, Acteur* player_array, int player_amount);
    void init_stage(SDL_Renderer* renderTarget, Map* map_ptr, int map_amount, Stage* stage, Random& random, Acteur* player_array, int player_amount, Acteur* entity_array, int entity_amount, Chest* chest);
    void InitMapArray(Tile* tileArray, int tileAmount, Prop* propArray, int propAmount, Map* mapArray, int mapAmount);
    template<typename T>
    void init_grid_coords(T* array, int size, int height, int width);

    SDL_Renderer* renderTarget;

    void init_game(Tile* tileArray, int tileAmount, Prop* propArray, int propAmount, Map* mapArray, int mapAmount, Acteur* entity_array, int entity_amount, Acteur* player_array, int player_amount, Chest* chest);

private:
    Stage& stage;
    Random& random;
    Map* mapArray;
    int mapAmount;

    int controller_number;
};

template<typename T>
inline void Prologue::init_grid_coords(T* array, int size, int height, int width)
{
    int x_cord = 0;
    int y_cord = 0;

    int i = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            x_cord = w * 64;
            y_cord = h * 64;
            array[i].set_cords(x_cord, y_cord);
            i++;
        }
    }
}
