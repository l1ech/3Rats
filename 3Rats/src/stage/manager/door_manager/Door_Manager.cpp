#include "Door_Manager.h"
#include <SDL.h>
#include <SDL_log.h>

Door_Manager::Door_Manager(int width, int height, Random* random_ptr)
    : width(width), height(height), random_ptr(random_ptr)
{
    doors.resize(3);
    SDL_Log("[Door_Manager]: Initialized with width: %d, height: %d", width, height);
}

Door_Manager::Door_Manager()
{
    doors.resize(3);
    SDL_Log("[Door_Manager]: Initialized with default settings");
}

Door_Manager::~Door_Manager()
{
    SDL_Log("[Door_Manager]: Destructor called");
    // If there is any cleanup logic to do, add it here.
}

void Door_Manager::set_width(int width)
{
    this->width = width;
    SDL_Log("[Door_Manager]: Set width to: %d", width);
}

void Door_Manager::set_height(int height)
{
    this->height = height;
    SDL_Log("[Door_Manager]: Set height to: %d", height);
}

void Door_Manager::set_random_ptr(Random *random_ptr)
{
    this->random_ptr = random_ptr;
    SDL_Log("[Door_Manager]: Random pointer set");
}

void Door_Manager::generate_door(int direction, int index, int type, bool active)
{
    // direction => 0 = north, 1 = east, 2 = south, 3 = west
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
            SDL_Log("[Door_Manager]: Generated door at index %d with type %d at (%d, %d)", index, type, doors[index].get_x(), doors[index].get_y());
        }
        else
        {
            doors[index].init_door(-100, -100, type, active);
            SDL_Log("[Door_Manager]: Inactive door at index %d with type %d", index, type);
        }
    }
    else
    {
        switch (direction)
        {
        case 0:
            doors[index].init_door(random_ptr->roll_custom_dice(9), 1, type, active);
            SDL_Log("[Door_Manager]: Generated north door at index %d with type %d", index, type);
            break;
        case 1:
            doors[index].init_door(9, random_ptr->roll_custom_dice(6), type, active);
            SDL_Log("[Door_Manager]: Generated east door at index %d with type %d", index, type);
            break;
        case 2:
            doors[index].init_door(random_ptr->roll_custom_dice(9), 6, type, active);
            SDL_Log("[Door_Manager]: Generated south door at index %d with type %d", index, type);
            break;
        case 3:
            doors[index].init_door(1, random_ptr->roll_custom_dice(6), type, active);
            SDL_Log("[Door_Manager]: Generated west door at index %d with type %d", index, type);
            break;
        default:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Door_Manager]: Invalid direction %d for door generation", direction);
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
        SDL_Log("[Door_Manager]: Generated doors for MAZE_TYPE");
        break;
    case GARDEN_TYPE:
        for (int i = 0; i < 3; i++) 
            generate_door(direction[i], i, i + 1, active[GARDEN_TYPE][i]);
        SDL_Log("[Door_Manager]: Generated doors for GARDEN_TYPE");
        break;
    case CAGE_TYPE:
        for (int i = 0; i < 3; i++) 
            generate_door(direction[i], i, i + 1, active[CAGE_TYPE][i]);
        SDL_Log("[Door_Manager]: Generated doors for CAGE_TYPE");
        break;
    default:
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Door_Manager]: Error generating doors with type %d", type_generation);
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
    SDL_Log("[Map]: Entry [%d; %d]", doors[0].get_x(), doors[0].get_y());
    SDL_Log("[Map]: Exit [%d; %d]", doors[1].get_x(), doors[1].get_y());
    SDL_Log("[Map]: Hole [%d; %d]", doors[2].get_x(), doors[2].get_y());
}

void Door_Manager::place_doors(std::vector<std::vector<int>>& data)
{
    if (doors[0].get_active()) {
        data[doors[0].get_y()][doors[0].get_x()] = 2;
        SDL_Log("[Door_Manager]: Placed entry door at (%d, %d)", doors[0].get_x(), doors[0].get_y());
    }

    if (doors[1].get_active()) {
        data[doors[1].get_y()][doors[1].get_x()] = 0;
        SDL_Log("[Door_Manager]: Placed exit door at (%d, %d)", doors[1].get_x(), doors[1].get_y());
    }

    if (doors[2].get_active()) {
        data[doors[2].get_y()][doors[2].get_x()] = 13;
        SDL_Log("[Door_Manager]: Placed hole door at (%d, %d)", doors[2].get_x(), doors[2].get_y());
    }
}

Door Door_Manager::get_door(int index) { return doors[index]; }
