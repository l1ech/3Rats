#include "Body.h"

Body::Body() { 
    index = current_index++; 
    std::cout << "CONSTRUCTOR BODY: " << index << std::endl;
}

Body::~Body() { 
    SDL_DestroyTexture(texture); 
    std::cout << "DESTRUCTOR BODY: " << index << std::endl;
}

void Body::update(float delta) { 
    // Add any debugging here if needed
}

void Body::draw(SDL_Renderer* renderTarget) { 
    if (texture != nullptr) {
        SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect);
        //std::cout << "Body <" << index << "> draw at position x: " << position_rect.x << ", y: " << position_rect.y << ", width: " << position_rect.w << ", height: " << position_rect.h << std::endl;
    } else {
        std::cerr << "Error Body <"<< name << ">;<" << index << "> Attempted to draw without texture." << std::endl;
    }
}

void Body::set_surface(SDL_Renderer* renderTarget)
{
    std::cout << "Body <"<< name << ">;<" << index << "> set_surface called for file: " << file_path << std::endl;
    
    Collage collage;
    file_path = collage.get_path(2);
    ptr_renderer = renderTarget;

    SDL_Surface* surface = IMG_Load(file_path.c_str());
    if (surface == NULL) {
        std::cerr << "Error Body <"<< name << ">;<" << index << "> Surface: " << file_path << " - " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
        if (texture == NULL) {
            std::cerr << "Error Body <"<< name << ">;<" << index << "> Texture: " << file_path << " - " << SDL_GetError() << std::endl;
        } else {
            SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);
        }
    }

    SDL_FreeSurface(surface);
}

void Body::set_texture(const std::string& filePath)
{
    std::cout << "Body <"<< name << ">;<" << index << "> set_texture called for file: " << filePath << std::endl;
    
    this->file_path = filePath;
    SDL_Surface* surface = IMG_Load(file_path.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image for Body <" << index << ">: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(ptr_renderer, surface);
        SDL_FreeSurface(surface);

        if (texture == nullptr) {
            std::cerr << "Failed to create texture for Body <"<< name << ">;<" << index << ">: " << SDL_GetError() << std::endl;
        } else {
            SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);
        }
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

    std::cout << "Body <"<< name << ">;<" << index << "> set_cords to x: " << x << ", y: " << y << std::endl;
}

void Body::set_hight(int value) { 
    this->hight = value;
    std::cout << "Body <"<< name << ">;<" << index << "> set height to: " << value << std::endl;
}

void Body::set_name(std::string name)
{
	this->name = name;
}

int Body::get_hight() { 
    return this->hight; 
}

int Body::get_index() { 
    return index; 
}

std::string Body::get_name()
{
    return name;
}

int Body::get_origin_x() { 
    return position_rect.x + origin_x; 
}

int Body::get_origin_y() { 
    return position_rect.y + origin_y; 
}

int Body::get_radius() { 
    return radius; 
}
