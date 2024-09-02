// Setup.h
#pragma once
#include <SDL.h>
#include "Acteur.h"
#include "Stage.h"
#include "Random.h"
#include "Map.h"

class Setup {
public:
    Setup(SDL_Renderer* renderer, Stage& stage, Random& random);
    bool Initialize();
    void InitEntityArray(Acteur entityArray[], int entityAmount, int& controllerNum);
    void InitPlayerArray(Acteur playerArray[], int playerAmount, int& controllerNum);
    void InitStage(Map mapArray[], int mapAmount);
    void init_stage(SDL_Renderer* renderTarget, Map* map_ptr, int map_amount, Stage* stage, Random& random);
    SDL_Renderer* renderTarget;

private:
    Stage& stage;
    Random& random;
    Map* mapArray;
    int mapAmount;
};
