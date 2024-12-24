// texture_utils.cpp
#include "utils.h"
#include <SDL2/SDL_log.h>

std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> LoadTexture(const std::string& filePath, SDL_Renderer* renderTarget)
{
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> texture(nullptr, SDL_DestroyTexture);
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Error loading surface: %s", IMG_GetError());
    } else {
        texture.reset(SDL_CreateTextureFromSurface(renderTarget, surface));
        if (texture == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Error creating texture from surface: %s", SDL_GetError());
        } else {
            SDL_Log("[Main]: Texture loaded successfully from: %s", filePath.c_str());
        }
    }

    SDL_FreeSurface(surface);

    return texture;
}
