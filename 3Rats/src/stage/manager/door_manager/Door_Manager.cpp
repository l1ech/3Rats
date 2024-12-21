#include "Door_Manager.h"

Door_Manager::Door_Manager(int width, int height, Random* random_ptr)
    : width(width), height(height), random_ptr(random_ptr)
{
    doors.resize(3);  
    std::cout << "[Door_Manager]: initialized with width: " << width
              << ", height: " << height << std::endl;
}

Door_Manager::Door_Manager()
{
        doors.resize(3); 
        std::cout << "[Door_Manager]: initialized" << std::endl;
}

Door_Manager::~Door_Manager()
{
}

void Door_Manager::set_width(int width)
{
    this->width = width;
}

void Door_Manager::set_height(int height)
{
    this->height = height;
}

void Door_Manager::set_random_ptr(Random *random_ptr)
{
    this->random_ptr = random_ptr;
}

void Door_Manager::generate_door(int direction, int index, int type, bool active)
{
    //direction => 0 = north, 1 = east, 2 = south, 3 = west
    if (direction == 5)
    {
        if (active)
        {
            doors[index].init_door
            (
                random_ptr->roll_custom_dice(width), 
                random_ptr->roll_custom_dice(height),
                type, 
                active
            );
        }
        else
        {
            doors[index].init_door(-100, -100, type, active);
        }
    }
    else
    {
        switch (direction)
        {
        case 0:
            doors[index].init_door(random_ptr->roll_custom_dice(9), 1, type, active);
            break;
        case 1:
            doors[index].init_door(9, random_ptr->roll_custom_dice(6), type, active);
            break;
        case 2:
            doors[index].init_door(random_ptr->roll_custom_dice(9), 6, type, active);
            break;
        case 3:
            doors[index].init_door(1, random_ptr->roll_custom_dice(6), type, active);
            break;
        default:
            std::cout << "[Door_Manager]: error" << std::endl;
            break;
        }
    }    
}

void Door_Manager::generate_doors(int entry_direction, int exit_direction, int type_generation)
{
    const int MAZE_TYPE = 0;
    const int GARDEN_TYPE = 1;
    const int CAGE_TYPE = 2;

    const int INVALID_DIRECTION = 5;

    const int DOOR_TYPE_AMOUNT = 3;
    const int DOOR_AMOUNT = 3;

    int direction[DOOR_AMOUNT] = 
    { 
        entry_direction, 
        exit_direction, 
        INVALID_DIRECTION 
    };

    bool active[DOOR_TYPE_AMOUNT][DOOR_AMOUNT] =
    {
        {true, true, false},    // maze
        {true, true, true},     // garden
        {false, false, true}    // cage
    };

    switch (type_generation)
    {
    case MAZE_TYPE:
        for (int i = 0; i < 3; i++) 
            generate_door(direction[i], i, i + 1, active[MAZE_TYPE][i]);
        break;
    case GARDEN_TYPE:
        for (int i = 0; i < 3; i++) 
            generate_door(direction[i], i, i + 1, active[GARDEN_TYPE][i]);
        break;
    case CAGE_TYPE:
        for (int i = 0; i< 3; i++)
            generate_door(direction[i], i, i + 1, active[CAGE_TYPE][i]);
        break;
    default:
        std::cout << "[Door_Manager]: error generating doors!";
        break;
    }    
}


// Getter methods
std::vector<Door>& Door_Manager::get_doors() {
    return doors;
}

Random* Door_Manager::get_random_ptr() {
    return random_ptr;
}

int Door_Manager::get_width() const {
    return width;
}

int Door_Manager::get_height() const {
    return height;
}


void Door_Manager::print_doors()
{
    std::cout << "[Map]: Entry [" << doors[0].get_x() << ";" << doors[0].get_y() << "]" << std::endl;
    std::cout << "[Map]: Exit [" << doors[1].get_x() << ";" << doors[1].get_y() << "]" << std::endl;
    std::cout << "[Map]: Hole [" << doors[2].get_x() << ";" << doors[2].get_y() << "]" << std::endl;
}

void Door_Manager::place_doors(std::vector<std::vector<int>>& data)
{
    if (doors[0].get_active())
        data[doors[0].get_y()][doors[0].get_x()] = 2;

    if (doors[1].get_active())
        data[doors[1].get_y()][doors[1].get_x()] = 0;

    if (doors[2].get_active())
        data[doors[2].get_y()][doors[2].get_x()] = 13;
}

Door Door_Manager::get_door(int index) { return doors[index]; }
