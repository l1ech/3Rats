// texture_utils.h
#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include <memory>

// Utility function to load textures
std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> LoadTexture(const std::string& filePath, SDL_Renderer* renderTarget);

#endif // TEXTURE_UTILS_H
