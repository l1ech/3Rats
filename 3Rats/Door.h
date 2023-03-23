#pragma once

#include<utility>

class Door
{
private:
	int type;	// 0 = undefined, 1 = entry, 2 = exit, 3 = hole
	int x, y;

public:
	Door(int x_pos, int y_pos, int t);
	Door();

	int get_x();
	int get_y();
	int get_type();

	void init_door(int x_pos, int y_pos, int t);
	void set_cords(int x_pos, int y_pos);
};