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

void Map::trim_vector(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data)
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }
}

void Map::set_new_srand()
{
    //srand(time(NULL));
}

int Map::rec_pos(int x, int y, std::vector<std::vector <int>>& arg)
{
    //std::cout<<"setting xy: "<<x<<"; "<<y<<std::endl;
    //print_vector(arg, width+2, height+2);

    //std::cout << "rec_pos opend" <<std::endl;
    //std::cout<< "__________________________________"<<std::endl;


    //================= set new location
    if (flip_coin())
    {//horizontal
        if (flip_coin()) x++; //right
        else x--; //left
    }
    else
    {//vertical
        if (flip_coin()) y++; //up
        else y--; //down
    }
    //================= try new location

    if (arg[y][x] == 1) return 1;
    else if (arg[y][x] == 0)
    {
        arg[y][x] = 1;
        int vall = rec_pos(x, y, arg);
        if (vall == 1)
        {
            arg[y][x] = 0;
            return 1;
        }
        else if (vall == 2) return 2;
        else return 7;
    }
    else if (arg[y][x] == 2) return 2;
    else return 9;
    return 8;
}

void Map::make_maze()
{
    width = 9;
    height = 6;

    int iter = 0;

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));

    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if (w == 0 || w == width+1 || h == 0 || h == height+1) data[h][w] = 1;
            else data[h][w] = 0;

        }
    }

    data[1][1] = 1;
    data[height][width] = 2;

    print_vector(data, width + 2, height + 2);

    int end_x = 10;
    int end_y = 7;
    int start_x = 1;
    int start_y = 1;

    int val;

    while (1)
    {
        //std::cout << "iter: " << iter << std::endl;
        //iter++;

        val = rec_pos(start_x, start_y, data);

        if (val == 1)
        {
            //std::cout << "rec_pos hit wall!" << std::endl;
        }
        else if (val == 2)
        {
            std::cout << "found exit!" << std::endl;
            break;
        }
        else {
            //std::cout << "value not allowed!" << std::endl;
        }

        //std::cout << "val: " << val << std::endl;

    }
    print_vector(data, width + 2, height + 2);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }

    print_vector(map_data, map_data[0].size(), map_data.size());

    for (int h = 0; h < map_data.size(); h++)
    {
        for (int w = 0; w < map_data[0].size(); w++)
        {
            if (map_data[h][w] == 1) 
            {
                body_array[get_tile(w, h)].set_texture("walk_way.png");
            }
            else if (map_data[h][w] == 0)
            {
                body_array[get_tile(w, h)].set_texture("maze_wall.png");
            }
        }
        std::cout << std::endl;
    }
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




