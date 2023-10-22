#pragma once

#include "Text.h"
#include "Overlay.h"

class Button : public Text
{
public:
    Button(SDL_Renderer* renderer, int x, int y, int width, int height);

    void render();
    void handleEvent(const SDL_Event& event);
    void set_overlay(Overlay* overlay);

private:
    Overlay* overlay;

    SDL_Renderer* renderer;
    SDL_Rect rect;
    bool clicked;
};
