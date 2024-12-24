#include "Body.h"
Body::Body() : hight(0), width(0), name("NULL"), index(current_index++) {  
    SDL_Log("[Body_%d](%s): CONSTRUCTOR BODY", index, name.c_str());
}

Body::~Body() { 
    SDL_Log("[Body_%d](%s): DESTRUCTOR BODY", index, name.c_str());
    SDL_DestroyTexture(texture); 
}

void Body::update(float delta) { 
    // Add any debugging here if needed
}
void Body::draw(SDL_Renderer* ptr_renderer) const {
    //SDL_Log("[Body_%d](%s): draw called", index, name.c_str());

    // Check if renderer is valid
    if (ptr_renderer == nullptr) {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error with Renderer is null. Cannot draw.", index, name.c_str());
        return;
    }

    // Check if texture is valid
    if (texture == nullptr) {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error with Texture is null. Cannot draw.", index, name.c_str());
        return;
    }

    // Check crop rectangle dimensions
    if (crop_rect.w <= 0 || crop_rect.h <= 0) {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error with Invalid crop rectangle dimensions: width=%d, height=%d. Cannot draw.", index, name.c_str(), crop_rect.w, crop_rect.h);
        return;
    }

    // Check position rectangle dimensions
    if (position_rect.w <= 0 || position_rect.h <= 0) {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error with Invalid position rectangle dimensions: width=%d, height=%d. Cannot draw.", index, name.c_str(), position_rect.w, position_rect.h);
        return;
    }

    // Attempt to draw
    if (SDL_RenderCopy(ptr_renderer, texture, &crop_rect, &position_rect) != 0) {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error with SDL_RenderCopy failed: %s", index, name.c_str(), SDL_GetError());
    } else {
        //SDL_Log("[Body_%d](%s): %s drawn successfully at position x: %d, y: %d, width: %d, height: %d", index, name.c_str(), name.c_str(), position_rect.x, position_rect.y, position_rect.w, position_rect.h);
    }
}
void Body::set_surface(SDL_Renderer* ptr_renderer) {
    SDL_Log("[Body_%d](%s): %s set_surface called", index, name.c_str(), name.c_str());
    this->ptr_renderer = ptr_renderer;
}

void Body::set_texture_path(const std::string& filePath) {
    texture = LoadTexture(filePath, ptr_renderer);
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Failed to load texture from %s", index, name.c_str(), filePath.c_str());
    } else {
        SDL_Log("[Body_%d](%s): Texture loaded successfully from %s", index, name.c_str(), filePath.c_str());
    }
}

void Body::set_cords(int x, int y) {
    SDL_Log("[Body_%d](%s): %s set_cords called with x: %d, y: %d", index, name.c_str(), name.c_str(), x, y);

    position_rect.x = x;
    position_rect.y = y;

    texture_width = crop_rect.w;

    frame_width = position_rect.w = crop_rect.w;
    frame_height = position_rect.h = crop_rect.h;

    origin_x = frame_width / 2;
    origin_y = frame_height / 2;

    radius = frame_width / 2;

    SDL_Log("[Body_%d](%s): set_cords to x: %d, y: %d", index, name.c_str(), x, y);
}

void Body::set_hight(int value) { 
    this->hight = value;
    SDL_Log("[Body_%d](%s): set height to: %d", index, name.c_str(), value);
}

void Body::set_name(const std::string& n) {
    if (n.empty()) {
        SDL_Log("[Body_%d](%s): set name called with empty string. Ignoring.", index, name.c_str());
        return;
    }
    SDL_Log("[Body_%d](%s): set name to: %s", index, name.c_str(), n.c_str());

    name = n;
}

int Body::get_hight() const { 
    return this->hight; 
}

int Body::get_index() const { 
    return index; 
}

std::string Body::get_name() const { 
    return name;
}

// TODO: move to utility class and make util-class
SDL_Texture* Body::LoadTexture(const std::string& filePath, SDL_Renderer* ptr_renderer) {
    SDL_Log("[Body_%d](%s): LoadTexture called for file: %s", index, name.c_str(), filePath.c_str());
    
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error loading surface: %s", index, name.c_str(), IMG_GetError());
    } else {
        texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
        if (texture == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Body_%d](%s): Error creating texture: %s", index, name.c_str(), SDL_GetError());
        } else {
            SDL_Log("[Body_%d](%s): Texture created successfully from surface", index, name.c_str());
        }
        SDL_FreeSurface(surface);
    }
    
    return texture;
}

int Body::get_origin_x() const { 
    return position_rect.x + origin_x; 
}

int Body::get_origin_y() const { 
    return position_rect.y + origin_y; 
}

int Body::get_radius() const{ 
    return radius; 
}
