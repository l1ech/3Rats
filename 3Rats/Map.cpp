#include "Map.h"

Map::Map()
{
    rec_iter = 0;
    width = 9;
    height = 6;

    item_id = 0;
}

Map::Map(const Map& b)
{
    rec_iter = 0;
    width = 9;
    height = 6;
    item_id = 0;
}

Map::Map(Tile arg[], int size, int w, int h, int type)
{
    rec_iter = 0;
	width = w;
	height = h;

    item_id = 0;

	tile_array = arg;
	tile_array_size = size;

	int x_cord = 0;
	int y_cord = 0;

	for (int i = 0; i < tile_array_size; i++)
	{
		tile_array[i].set_cords(x_cord, y_cord);
		//tile_array[i].set_texture("maze_wall.png");
		x_cord += 64;

		if (x_cord >= 576)
		{
			y_cord += 64;
			x_cord = 0;
		}
	}

    switch (type)
    {

    case 0:
        make_maze(true);
        break;

    case 1:
        make_garden(true);
        break;

    default:
        break;
    }
}

Map::~Map()
{
}

void Map::Update(float delta)
{
    
}

void Map::Draw(SDL_Renderer* renderTarget)
{
}


void Map::make_maze(bool item_generation)
{
    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    Random rand;

    entrence = { rand.roll_custom_dice(start_x), rand.roll_custom_dice(start_y) };
    exit = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };
    hole = { -100, -100 };

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));

    build_frame(data, entrence, exit, 9, 1);

    while (rec_pos(start_x, start_y, data, data[start_x][start_y]) != 0) { }

    trim_boarder(data, map_data);

    //print_vector(map_data, map_data[0].size(), map_data.size());

    //set_corners(map_data);

    if (item_generation) set_items_to_map(map_data, item_data, height, width, 70); // 80 meaning 1/80

    //print_vector(item_data, item_data[0].size(), item_data.size());

    save_data(map_data, item_data);
}

void Map::make_garden(bool item_generation)
{
    width = 9;
    height = 6;

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    Random rand;

    entrence = { rand.roll_custom_dice(start_x), rand.roll_custom_dice(start_y) };
    exit = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };
    hole = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));

    build_frame(data, entrence, exit, 1, 12);

    if (rand.roll_dice())
    {
        std::cout << hole.first << "  " << hole.second << std::endl;
        data[hole.second][hole.first] = 13;
    }


    trim_boarder(data, map_data);

    //print_vector(data, data[0].size(), data.size());

    if (item_generation) set_items_to_map(map_data, item_data, height, width, 70);  //20 meaning 1/20

    save_data(map_data, item_data);
}

void Map::make_cage(bool item_generation)
{
    width = 9;
    height = 6;

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    Random rand;


    exit = { -100, -100 };
    entrence = { -100, -100 };
    hole = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };

    std::pair<int, int> food_bowl = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };
    std::pair<int, int> bed = { rand.roll_custom_dice(end_x), rand.roll_custom_dice(end_y) };

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));

    build_frame(data, 1, 14);

    if (1)      // in this case it has to generate a hole. maybe not ?
                // maybe it generates a hole only if the player does an action?
                // for now for testing it is this
    {
        std::cout << hole.first << "  " << hole.second << std::endl;
        data[hole.second][hole.first] = 13;
    }

    data[food_bowl.second][food_bowl.first] = 15;
    data[bed.second][bed.first] = 16;


    trim_boarder(data, map_data);

    //print_vector(data, data[0].size(), data.size());

    //if (item_generation) set_items_to_map(map_data, item_data, height, width, 70);  //20 meaning 1/20

    save_data(map_data, item_data);
}


void Map::set_item_array(Item* item, int size)
{
    item_array = item;
    item_array_size = size;

    int x_cord = 0;
    int y_cord = 0;

    int i = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            x_cord = w * 64;
            y_cord = h * 64;
            item_array[i].set_cords(x_cord, y_cord);
            i++;
        }
    }
}

void Map::set_tile_array(Tile* tile, int size)
{   
    tile_array = tile;
    tile_array_size = size;

    int x_cord = 0;
    int y_cord = 0;

    int i = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            x_cord = w * 64;
            y_cord = h * 64;

            tile_array[i].set_cords(x_cord, y_cord);
            i++;
        }
    }
}

void Map::set_type(int type)
{
    switch (type)
    {

    case 0:
        make_maze(true);
        break;

    case 1:
        make_garden(true);
        break;
    case 2:
        make_cage(false);
        break;

    default:
        break;
    }
}

void Map::set_textures()
{
    /*
    Tile end_door(true, false, false, "maze_textures/maze_door.png", 0);
    Tile wall(false, false, false, "maze_textures/maze_wall.png", 1);
    Tile start_door(false, true, false, "maze_textures/maze_door.png", 0);
    Tile horizontal(false, false, false, "maze_textures/walk_way_shadow_horizontal.png", 0);
    Tile vertical(false, false, false, "maze_textures/walk_way_shadow_vertical.png", 0);
    Tile ground(false, false, false, "maze_textures/ground.png", 0);
    Tile maze_hole(false, false, true, "maze_textures/maze_hole.png", 0);

    */
    
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            Tile& inspected_tile = tile_array[get_tile(w, h)];
            Item& inspected_item = item_array[get_tile(w, h)];

            switch (data[h][w].first)
            {
                //maybe i should define some kind of object that
                // so that you could use this as a copy for the others 
                // less code more readable

                // make that next!

            case 0: //end_door
                inspected_tile.set_texture("maze_textures/maze_door.png");
                inspected_tile.is_exit = true;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 1: //wall
                
                inspected_tile.set_texture("maze_textures/maze_wall.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(1);
                
                
                //inspected_tile = maze_hole;

                break;

            case 2: //start_door
                inspected_tile.set_texture("maze_textures/maze_door.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = true;
                inspected_tile.set_hight(0);
                break;

            case 3: //right (horizontal)
            case 4: //left (horizontal)
                inspected_tile.set_texture("maze_textures/walk_way_shadow_horizontal.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 5: //up (vertical)
            case 6: //down (vertical)
                //inspected_tile.set_texture("maze_textures/ground.png");
                inspected_tile.set_texture("maze_textures/walk_way_shadow_vertical.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 7: //left-up
                //inspected_tile.set_texture("maze_textures/walk_way_shadow_left_up.png");
                inspected_tile.set_texture("maze_textures/ground.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 8: //right-up 
                //inspected_tile.set_texture("maze_textures/walk_way_shadow_right_down.png");
                inspected_tile.set_texture("maze_textures/ground.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 9: //left-down
                //inspected_tile.set_texture("maze_textures/walk_way_shadow_left_down.png");
                inspected_tile.set_texture("maze_textures/ground.png");
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_hight(0);
                break;

            case 10: //right-down
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_texture("maze_textures/ground.png");
                //inspected_tile.set_texture("maze_textures/walk_way_shadow_right_down.png");
                break;

            case 11: //hard-wall 
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_texture("maze_textures/ground.png");
                //inspected_tile.set_texture("maze_textures/maze_wall.png");
                break;

            case 12:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_hole = false;
                inspected_tile.is_entrance = false;
                inspected_tile.set_texture("maze_textures/ground.png");
                //inspected_tile.set_texture("place_holder.png");
                break;
            case 13:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_entrance = false;
                inspected_tile.is_hole = true;
                inspected_tile.set_texture("maze_textures/maze_hole.png");
                break;
            case 14:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_entrance = false;
                inspected_tile.is_hole = false;
                inspected_tile.set_texture("maze_textures/place_holder.png");
                break;

            case 15:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_entrance = false;
                inspected_tile.is_hole = false;
                inspected_tile.set_texture("textures/interactable/test.png");
                break;

            case 16:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_entrance = false;
                inspected_tile.is_hole = false;
                inspected_tile.set_texture("textures/interactable/test.png");
                break;

            default:
                inspected_tile.set_hight(0);
                inspected_tile.is_exit = false;
                inspected_tile.is_entrance = false;
                inspected_tile.is_hole = false;
                inspected_tile.set_texture("maze_textures/place_holder.png");
                break;
            }

            int x_cord = w * 64;
            int y_cord = h * 64;

            if (data[h][w].second == 1)
            {
                inspected_item.set_on_map(true);
                inspected_item.set_cords(x_cord, y_cord);
                inspected_item.set_texture("item_textures/mushroom.png");
                item_id++;
            }
            else if (data[h][w].second == 0)
            {
                inspected_item.set_on_map(false);
                inspected_item.set_cords(-100, -100);
                inspected_item.set_texture("item_textures/place_holder.png");
            }
        }
    }
}


void Map::show_it()
{
    std::cout << "iteration: " << rec_iter << std::endl;
    rec_iter = 0;
}

void Map::set_ptr(int* ptr)
{
    item_on_map = ptr;
}

void Map::set_map_id(int numer) { map_id = numer; }

int Map::get_map_id() { return map_id; }

std::pair <int, int> Map::give_entry_door() { return { entrence.first, entrence.second }; }

std::pair<int, int> Map::give_exit_door() { return { exit.first, exit.second }; }

std::pair<int, int> Map::give_hole_door() { return { hole.first, hole.second }; }

int Map::rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction)
{
    Random rand;

    rec_iter++;
    int direction;

    //print_vector(arg, width + 2, height + 2);

    //================= set new location
    if (rand.flip_coin())
    {//horizontal
        if (rand.flip_coin())
        {
            direction = 3;
            x++;
        }//right
        else
        {
            direction = 4;
            x--;
        }//left
    }
    else
    {//vertical
        if (rand.flip_coin())
        {
            direction = 5;
            y++;
        }//up
        else
        {
            direction = 6;
            y--;
        }//down
    }
    //================= try new location

    int point_value = arg[y][x];

    if (point_value == 0)                         // finish or path
    {
        return point_value;
    }
    else if (point_value == 1)                    // empty field == wall
    {
        arg[y][x] = direction;

        int vall = rec_pos(x, y, arg, direction);

        if (vall == 0)
        {
            directions.push_back(direction);
            return vall;
        }
        else if (vall == 1)
        {

            arg[y][x] = direction;
        }
        else
        {
            arg[y][x] = 1;
            return vall;
        }
    }
    else
    {
        return point_value;
    }
}

void Map::build_frame(std::vector<std::vector <int>>& data, std::pair<int, int >entrance, std::pair<int, int >exit, int wall, int space)
{
    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (w == 0 || w == width + 1 || h == 0 || h == height + 1) data[h][w] = wall;
            else data[h][w] = space;

        }
    }

    data[entrance.second][entrance.first] = 2;
    data[exit.second][exit.first] = 0;
}

void Map::build_frame(std::vector<std::vector <int>>& data, int wall, int space)
{
    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (w == 0 || w == width + 1 || h == 0 || h == height + 1) data[h][w] = wall;
            else data[h][w] = space;

        }
    }
}

void Map::print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y)
{
    std::cout << "vector: " << std::endl;

    for (int h = 0; h < size_y; h++)
    {
        for (int w = 0; w < size_x; w++)
        {
            std::cout << arg[h][w];

        }
        std::cout << std::endl;
    }
}

void Map::trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data)   //trim boarder
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }
}

void Map::set_corners(std::vector<std::vector<int>>& map_data)
{
    int direction, prev_direction;

    for (int i = directions.size() - 1; i > 0; i--)
    {
        prev_direction = directions[i];
        direction = directions[i - 1];

        if (prev_direction == direction) { }
        else if (prev_direction == 3)
        {
            if (direction == 5)
            { 
                directions[i] = 9;
            }
            else if (direction == 6)
            {
                directions[i] = 8;
            }
        }
        else if (prev_direction == 4)
        {
            if (direction == 5)
            {
                directions[i] = 7;
            }
            else if (direction == 6)
            {
                directions[i] = 9;
            }
        }
        else if (prev_direction == 5)
        {
            if (direction == 3)
            {
                directions[i] = 10;
            }
            else if (direction == 4)
            {
                directions[i] = 11;
            }
        }
        else if (prev_direction == 6)
        {
            if (direction == 3)
            {
                directions[i] = 12;
            }
            else if (direction == 4)
            {
                directions[i] = 13;
            }
        }
        else
        {
            std::cout << "ERROR DIRECTION" << std::endl;
        }
    }
}

void Map::save_data(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            data[i][j].first = map_data[i][j];
            data[i][j].second = item_data[i][j];
        }
    }
}

void Map::set_items_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data, int height, int width, int probability)
{
    Random rand;

    std::cout << *item_on_map << std::endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map_data[i][j] == 0 || map_data[i][j] == 1 || map_data[i][j] == 2)
            {
                item_data[i][j] = 0;
            }
            else if (*item_on_map < item_array_size && rand.roll_custom_dice(probability) == 1)
            {
                item_data[i][j] = 1;
                (*item_on_map)++;
            }
            
        }
    }

}


int Map::get_tile(int x, int y)
{
    return y * width + x;
}