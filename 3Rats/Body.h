#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>

class Body
{
private:

protected:

	std::string texture_path;
	SDL_Renderer* render_target;
	SDL_Texture* texture;

	SDL_Rect position_rect;
	SDL_Rect crop_rect;

	float frame_width, frame_height;
	int texture_width;

	int origin_x, origin_y;
	int radius;

	int hight;
	double weight;		
	// make it that this affacts 
	// how fast it can be carried arround
	// maybe: if two rats need 
	// to carry it together?

public:

	Body();
	~Body();

	void update(float delta);
	void draw(SDL_Renderer* render_target);

	void set_renderer(SDL_Renderer* render_target);

	//void init(std::string path, int x, int y, int h, int framesX, int framesY);
	void set_texture(std::string path);
	void set_cords(int x, int y);
	void set_hight(int h);
	void set_cords_frames(int x, int y, int framesX, int framesY);

	int get_origin_x();
	int get_origin_y();
	int get_radius();
	int get_hight();
};