#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

class Body
{
private:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	SDL_Rect positionRect;

	SDL_Renderer* ptr_renderer;

	float moveSpeed;
	float frameCounter, searchCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	bool isActive;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;
	std::string filePath;

	int hight;

public:

	bool is_exit, is_entrance;

	Body();
	Body(int x, int y);
	Body(SDL_Renderer* renderTarget, int x, int y);
	Body(const Body& b);
	~Body();

	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	int GetOriginX();
	int GetOriginY();
	int GetRadius();
	void set_hight(int value);
	int get_hight();

	void SetX(int x);
	void SetY(int y);

	void set_surface(SDL_Renderer* renderTarget);
	void set_cords(int x, int y);
	void set_texture(std::string name);

};