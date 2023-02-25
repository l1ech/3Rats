#include "Map.h"
#include <fstream>
#include <vector>

bool Map::flip_coin()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);

    return dist1(rng);
}


Map::Map(const Map& b)
{

}

Map::Map()
{

}


Map::Map(Body arg[], int size, int w, int h)
{
    rec_iter = 0;
	width = w;
	height = h;

	body_array = arg;
	body_amount = size;

	int x_cord = 0;
	int y_cord = 0;

	for (int i = 0; i < body_amount; i++)
	{
		body_array[i].set_cords(x_cord, y_cord);
		//body_array[i].set_texture("maze_wall.png");
		x_cord += 64;

		if (x_cord >= 576)
		{
			y_cord += 64;
			x_cord = 0;
		}
	}

    srand(time(NULL));

}

Map::~Map()
{
}

int Map::get_tile(int x, int y)
{
	return y * width + x;
}

void Map::print_vector(std::vector<std::vector <int>>& arg, int size_x, int size_y)
{
    std::cout << "vector: " << std::endl;

    std::ofstream myfile;
    myfile.open("maze_gen.txt");

    for (int h = 0; h < size_y; h++)
    {
        for (int w = 0; w < size_x; w++)
        {
            myfile << arg[h][w];
            std::cout << arg[h][w];

        }
        myfile << "\n";
        std::cout << std::endl;
    }
    myfile.close();
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

int Map::rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int prev_direction)
{
    rec_iter++;
    int direction;

    //================= set new location
    if (flip_coin())
    {//horizontal
        if (flip_coin())
        {
            direction = 3;
            x++;
        }//right
        else
        {
            direction = 3;
            x--;
        }//left
    }
    else
    {//vertical
        if (flip_coin())
        {
            direction = 4;
            y++;
        }//up
        else
        {
            direction = 4;
            y--;
        }//down
    }
    //================= try new location

    int point_value = arg[y][x];

    if (point_value == 2)                         // finish or path
    {
        return point_value;
    }
    else if (point_value == 1)                    // empty field == wall
    {
        arg[y][x] = get_direction(prev_direction, direction);
        int vall = rec_pos(x, y, arg, direction);
        if (arg[y][x] == 3 || arg[y][x] == 4)
        {
            arg[y][x] = direction;
            return 2;
        }
        else if (vall == 0) return 0;
        else return 7;
    }
    else
    {
        return 9;
    }
}

int Map::get_direction(int prev_direction, int direction)
{
    return direction;
}

void Map::show_it()
{
    std::cout << "iteration: " << rec_iter << std::endl;
    rec_iter = 0;
}

void Map::set_textures(std::vector<std::vector <int>>& map_data)
{
    for (int h = 0; h < map_data.size(); h++)
    {
        for (int w = 0; w < map_data[0].size(); w++)
        {
            switch (map_data[h][w])
            {
            case 0: //end_door
                body_array[get_tile(w, h)].set_texture("maze_textures/maze_door.png");
                break;

            case 1: //wall
                body_array[get_tile(w, h)].set_texture("maze_textures/maze_wall.png");
                break;

            case 2: //start_door
                body_array[get_tile(w, h)].set_texture("maze_textures/maze_door.png");
                break;

            case 3: //horizontal
                body_array[get_tile(w, h)].set_texture("maze_textures/walk_way_shadow_horizontal.png");
                break;

            case 4: //vertical
                body_array[get_tile(w, h)].set_texture("maze_textures/walk_way_shadow_vertical.png");
                break;

            case 5: //left-up
                break;

            case 6: //left-down
                break;

            case 7: //right-up
                break;

            case 8: //right-down
                break;

            case 9: //hard-wall
                break;

            default:
                break;
            }
        }
    }
}

void Map::build_frame(std::vector<std::vector <int>>& data, int start_x, int start_y, int end_x, int end_y)
{
    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (w == 0 || w == width + 1 || h == 0 || h == height + 1) data[h][w] = 9;
            else data[h][w] = 1;

        }
    }

    data[start_x][start_y] = 2;
    data[end_x][end_y] = 0;
}

void Map::make_maze()
{
    width = 9;
    height = 6;

    int start_x = 1;
    int start_y = 1;

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));

    build_frame(data, start_x, start_y, height, width);

    print_vector(data, width + 2, height + 2);

    int val;

    while (1)
    {
        val = rec_pos(start_x, start_y, data, data[start_x][start_y]);

        if (val != 2)   // rec_pos hit path!
        {
        }
        else if (val == 2)  // found exit!
        {
            break;
        }
        else 
        {  
            std::cout << "ERROR: value not allowed: " << val << std::endl;
            break;
        }
    }

    print_vector(data, width + 2, height + 2);

    trim_boarder(data, map_data);

    print_vector(map_data, map_data[0].size(), map_data.size());

    set_textures(map_data);
    
}

void Map::make_garden()
{

}

void Map::Update(float delta)
{
	//std::cout << "update" << std::endl;
}

void Map::Draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < body_amount; i++)
	{
		body_array[i].Draw(renderTarget);
	}
}




