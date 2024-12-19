#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include <memory>
#include <filesystem>

#include "../core/Collage.h"

class Body
{
protected:
	SDL_Renderer* ptr_renderer;
	SDL_Texture* texture;

	std::string file_path;

	SDL_Rect position_rect;
	SDL_Rect crop_rect;

	float frame_width, frame_height;
	int texture_width;

	int origin_x, origin_y;
	int radius;

	int hight;

public:
	int index;
	static int current_index;
	std::string name;

	
	Body();
	~Body();

	void update(float delta);
	void draw(SDL_Renderer* render_target);

	void set_surface(SDL_Renderer* render_target);
	void set_texture(const std::string& filePath);
	void set_cords(int x, int y);
	void set_hight(int value);
	void set_name(const std::string& name);

	int get_origin_x() const;
	int get_origin_y() const;
	int get_radius() const;
	int get_hight() const;
	int get_index() const;
	std::string get_name() const;

	SDL_Texture* LoadTexture(const std::string& filePath, SDL_Renderer* renderTarget);
};