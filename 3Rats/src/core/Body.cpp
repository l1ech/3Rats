#include "Body.h"

Body::Body() : hight(0), width(0), name("NULL"), index(current_index++) {  
    std::cout << "[Body_" << index << "](" << name << "): CONSTRUCTOR BODY  " << std::endl;
    std::cout << std::endl;
}

Body::~Body() { 
    std::cout << "[Body_" << index << "](" << name << "): DESTRUCTOR BODY " << std::endl;
    std::cout << std::endl;
    SDL_DestroyTexture(texture); 
}

void Body::update(float delta) { 
    // Add any debugging here if needed
}

void Body::draw(SDL_Renderer* ptr_renderer) const {
    std::cout << "[Body_" << index << "](" << name << "): draw called" << std::endl;

    // Check if renderer is valid
    if (ptr_renderer == nullptr) {
        std::cerr << "[Body_" << index << "](" << name << "): Error with Renderer is null. Cannot draw." << std::endl;
        return;
    }

    // Check if texture is valid
    if (texture == nullptr) {
        std::cerr << "[Body_" << index << "](" << name << "): Error with Texture is null. Cannot draw." << std::endl;
        return;
    }

    // Check crop rectangle dimensions
    if (crop_rect.w <= 0 || crop_rect.h <= 0) {
        std::cerr << "[Body_" << index << "](" << name << "): Error with Invalid crop rectangle dimensions: width=" << crop_rect.w << ", height=" << crop_rect.h << ". Cannot draw." << std::endl;
        return;
    }

    // Check position rectangle dimensions
    if (position_rect.w <= 0 || position_rect.h <= 0) {
        std::cerr << "[Body_" << index << "](" << name << "): Error with Invalid position rectangle dimensions: width=" << position_rect.w << ", height=" << position_rect.h << ". Cannot draw." << std::endl;
        return;
    }

    // Attempt to draw
    if (SDL_RenderCopy(ptr_renderer, texture, &crop_rect, &position_rect) != 0) {
        std::cerr << "[Body_" << index << "](" << name << "): Error with SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
        //
    } else {
        std::cout << "[Body_" << index << "](" << name << "): " << name << " drawn successfully at position x: "
                  << position_rect.x << ", y: " << position_rect.y << ", width: " << position_rect.w
                  << ", height: " << position_rect.h << std::endl;
    }
}

void Body::set_surface(SDL_Renderer* ptr_renderer) {
    std::cout << "[Body_" << index << "](" << name << "): " << name << " set_surface called" << std::endl;
    this->ptr_renderer = ptr_renderer;
}

void Body::set_texture(const std::string& filePath) {
    texture = LoadTexture(filePath, ptr_renderer);
    if (texture == nullptr) {
        std::cerr << "[Body_](" << name << "): Failed to load texture from " << filePath << std::endl;
    } else {
        std::cout << "[Body_](" << name << "): Texture loaded successfully from " << filePath << std::endl;
    }
}

void Body::set_cords(int x, int y)
{
    std::cout << "[Body_" << index << "](" << name << "): " << name << "set_cords called with x: " << x << ", y: " << y << std::endl;

    position_rect.x = x;
    position_rect.y = y;

    texture_width = crop_rect.w;

    frame_width = position_rect.w = crop_rect.w;
    frame_height = position_rect.h = crop_rect.h;

    origin_x = frame_width / 2;
    origin_y = frame_height / 2;

    radius = frame_width / 2;

    std::cout << "[Body_" << index << "](" << name << "): set_cords to x: " << x << ", y: " << y << std::endl;
}

void Body::set_hight(int value) { 
    this->hight = value;
    std::cout << "[Body_" << index << "](" << name << "): set height to: " << value << std::endl;
}

void Body::set_name(const std::string& n) {
    if (n.empty()) {
        std::cout << "[Body_" << index << "("<< name << "): set name called with empty string. Ignoring." << std::endl;
        return;
    }
    std::cout << "[Body_" << index << "](" << name << "): set name to: " << n << std::endl;

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
    std::cout << "[Body_" << index << "](" << name << "): LoadTexture called for file: " << filePath << std::endl;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "[Body_" << index << "](" << name << "): Error loading surface: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
        if (texture == nullptr) {
            std::cerr << "[Body_" << index << "](" << name << "): Error creating texture: " << SDL_GetError() << std::endl;
        } else {
            std::cout << "[Body_" << index << "](" << name << "): Texture created successfully from surface" << std::endl;
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
