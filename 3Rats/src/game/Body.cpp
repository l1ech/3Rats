#include "Body.h"

Body::Body() { 
    name = "NULL";
    index = current_index++; 
    std::cout << "[Body]: CONSTRUCTOR BODY: " << index << std::endl;
    std::cout << std::endl;
}

Body::~Body() { 
    SDL_DestroyTexture(texture); 
    std::cout << "[Body]: DESTRUCTOR BODY: " << index << std::endl;
    std::cout << std::endl;
}

void Body::update(float delta) { 
    // Add any debugging here if needed
}

void Body::draw(SDL_Renderer* ptr_renderer) {
    std::cout << "[Body]: " << name << "<" << index << "> draw called" << std::endl;

    // Check if renderer is valid
    if (ptr_renderer == nullptr) {
        std::cerr << "[Body]: Error with <" << name << ">;<" << index << "> Renderer is null. Cannot draw." << std::endl;
        return;
    }

    // Check if texture is valid
    if (texture == nullptr) {
        std::cerr << "[Body]: Error with <" << name << ">;<" << index << "> Texture is null. Cannot draw." << std::endl;
        return;
    }

    // Check crop rectangle dimensions
    if (crop_rect.w <= 0 || crop_rect.h <= 0) {
        std::cerr << "[Body]: Error with <" << name << ">;<" << index << "> Invalid crop rectangle dimensions: width=" << crop_rect.w << ", height=" << crop_rect.h << ". Cannot draw." << std::endl;
        return;
    }

    // Check position rectangle dimensions
    if (position_rect.w <= 0 || position_rect.h <= 0) {
        std::cerr << "[Body]: Error with <" << name << ">;<" << index << "> Invalid position rectangle dimensions: width=" << position_rect.w << ", height=" << position_rect.h << ". Cannot draw." << std::endl;
        return;
    }

    // Attempt to draw
    if (SDL_RenderCopy(ptr_renderer, texture, &crop_rect, &position_rect) != 0) {
        std::cerr << "[Body]: Error with <" << name << ">;<" << index << "> SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
        //
    } else {
        std::cout << "[Body]: " << name << " <" << index << "> drawn successfully at position x: "
                  << position_rect.x << ", y: " << position_rect.y << ", width: " << position_rect.w
                  << ", height: " << position_rect.h << std::endl;
    }
}

void Body::set_surface(SDL_Renderer* ptr_renderer) {
    std::cout << "[Body]: " << name << "<" << index << "> set_surface called" << std::endl;
    this->ptr_renderer = ptr_renderer;
}

void Body::set_texture(const std::string& filePath) {
    std::cout << "[Body]: " << name << "<" << index << "> set_texture called for file: " << filePath << std::endl;

    // Set file path
    // Use utility function to load the texture
    texture = LoadTexture(filePath, ptr_renderer);
    if (texture != nullptr) {
        SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h); // Get texture dimensions
        std::cout << "[Body]: " << name << "<" << index << "> Texture loaded successfully. Dimensions: width=" << crop_rect.w << ", height=" << crop_rect.h << std::endl;
    } else {
        std::cerr << "[Body]: " << name << "<" << index << "> Failed to load texture." << std::endl;
    }
}

void Body::set_cords(int x, int y)
{
    std::cout << "[Body]: " << name << "<" << index << "> set_cords called with x: " << x << ", y: " << y << std::endl;

    position_rect.x = x;
    position_rect.y = y;

    texture_width = crop_rect.w;

    frame_width = position_rect.w = crop_rect.w;
    frame_height = position_rect.h = crop_rect.h;

    origin_x = frame_width / 2;
    origin_y = frame_height / 2;

    radius = frame_width / 2;

    std::cout << "[Body]: "<< name << "<" << index << "> set_cords to x: " << x << ", y: " << y << std::endl;
}

void Body::set_hight(int value) { 
    this->hight = value;
    std::cout << "[Body]: "<< name << "<" << index << "> set height to: " << value << std::endl;
}

void Body::set_name(const std::string& name) { 
    this->name = name; 
    std::cout << "[Body]: "<< name << "<" << index << "> set name to: " << name << std::endl;
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
    std::cout << "[Body]: LoadTexture called for file: " << filePath << std::endl;
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "[Body]: Error loading surface: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
        if (texture == nullptr) {
            std::cerr << "[Body]: Error creating texture: " << SDL_GetError() << std::endl;
        } else {
            std::cout << "[Body]: Texture created successfully from surface" << std::endl;
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
