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

void Body::draw(SDL_Renderer* renderTarget) { 
    if (texture != nullptr) {
        SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect);
        std::cout << "[Body]: " << name << " <" << index << "> draw at position x: " << position_rect.x << ", y: " << position_rect.y << ", width: " << position_rect.w << ", height: " << position_rect.h << std::endl;
    } else {
        std::cerr << "[Body]: Error with <"<< name << ">;<" << index << "> Attempted to draw without texture." << std::endl;
    }
}

void Body::set_surface(SDL_Renderer* renderTarget) {
    std::cout << "[Body]: " << name << "<" << index << "> set_surface called for file: " << file_path << std::endl;
    
    // Retrieve file path from Collage (or other logic)
    Collage collage;
    file_path = collage.get_path(2);
    
    // Assign renderer
    ptr_renderer = renderTarget;

    // Use utility function to load the texture
    texture = LoadTexture(file_path, ptr_renderer);
    if (texture != nullptr) {
        SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h); // Get texture dimensions
    }
}
void Body::set_texture(const std::string& filePath) {
    std::cout << "[Body]: " << name << "<" << index << "> set_texture called for file: " << filePath << std::endl;

    // Set file path
    file_path = filePath;

    // Use utility function to load the texture
    texture = LoadTexture(file_path, ptr_renderer);
    if (texture != nullptr) {
        SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h); // Get texture dimensions
    }
}


void Body::set_cords(int x, int y)
{
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

void Body::set_name(const std::string& name) { this->name = name; }

int Body::get_hight() const { return this->hight; }

int Body::get_index() const { return index; }

std::string Body::get_name() const { return name;}

SDL_Texture* Body::LoadTexture(const std::string& filePath, SDL_Renderer* renderTarget) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "[Utility]: Error loading surface: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == nullptr) {
            std::cerr << "[Utility]: Error creating texture: " << SDL_GetError() << std::endl;
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
