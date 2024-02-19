#pragma once

#include <utility>

class Door
{
private:
	int type;	// 0 = undefined, 1 = entry, 2 = exit, 3 = hole
	int x, y;
	bool is_active;

public:
	Door(int x_pos, int y_pos, int t, bool active);
	Door();

	void init_door(int x_pos, int y_pos, int t, bool is_active);

	int get_x();
	int get_y();
	int get_type();
	bool get_active();

	void set_cords(int x_pos, int y_pos);
	void set_active(bool value);

};