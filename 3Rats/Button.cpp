#include "Button.h"

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height)
    : renderer(renderer), rect({ x, y, width, height }), clicked(false) {}

void Button::render() 
{
    if (clicked) 
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green when clicked
        overlay->play_music();
    }
    else 
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red when not clicked
        overlay->pause_music();
    }
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void Button::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h) {
            clicked = !clicked; // Toggle button state
            //render();
        }
    }
}

void Button::set_overlay(Overlay* overlay)
{
    this->overlay = overlay;
}
