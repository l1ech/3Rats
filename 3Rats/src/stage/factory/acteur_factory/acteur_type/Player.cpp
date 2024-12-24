#include "Player.h"

Player::Player()
{
    SDL_Log("[Player]: Constructor called");
}

Player::~Player()
{
    SDL_Log("[Player<%d>]: Destructor called", index);
    SDL_DestroyTexture(texture);
}


inline void Player::Update(float delta, const Uint8 *keyState, int mode, Acteur &front_rat)
{
    //SDL_Log("[Player<%d>]: Update called with delta: %.2f", index, delta);
    
    map_array = topography->get_map_array();
    map_array_size = topography->get_map_size();

    tile_array = topography->get_tile_array();
    tile_array_size = topography->get_tile_size();

    item_array = topography->get_item_array();
    item_array_size = topography->get_item_size();

    if (is_item_available_on_map())
    {
        make_goal();
    }
    else
    {
        mode = 0;
    }

    int rat_x = this->get_origin_x();
    int rat_y = this->get_origin_y();

    int frontRatX = front_rat.get_origin_x();
    int frontRatY = front_rat.get_origin_y();

    std::pair <int, int> offests = direction_to_offset(front_rat.GetDirection());

    rat_x += offests.first;
    rat_y += offests.second;

    std::vector<std::vector<bool>> collision_map;

    init_colision_map(collision_map);
    block_direction_counter collision_counter = { 0, 0, 0, 0 };
    block_direction direction = { 0, 0, 0, 0 };

    check_door(topography, map_array, map_array_size, tile_array, tile_array_size);

    collision_map = get_blocked_array(tile_array, tile_array_size);

    calculate_blocked_side(collision_counter, collision_map, tile_array_size);

    get_direction_blocked(collision_counter, direction, tile_array_size);

    controller_move move = {
        static_cast<bool>(keyState[keys[0]]),
        static_cast<bool>(keyState[keys[1]]),
        static_cast<bool>(keyState[keys[2]]),
        static_cast<bool>(keyState[keys[3]])
    };

    if (controller_number == 0)
    {
        make_acteur_move(move, direction, delta);
    }
    else
    {
        if (!wait)
        {
            if (mode == 1 && !holds_item)
            {
                follow_goal(rat_x, rat_y, goalX, goalY, direction, delta, item_array[item_search_id]);
            }
            else if (mode == 1 && holds_item)
            {
                follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, direction, delta, front_rat);
            }
            else if (mode == 0)
            {
                follow_front_rat(rat_x, rat_y, frontRatX, frontRatY, direction, delta, front_rat);
            }
        }
    }

    if (holds_item)
    {
        hold_item_in_mouth(item_array[item_hold_id]);
    }

    if (is_moving)
    {
        frameCounter += delta;
        searchCounter += delta;
        if (wait) waitCounter += delta;

        if (frameCounter >= 0.25f)
        {
            frameCounter = 0;
            crop_rect.x += frame_width;
            if (crop_rect.x >= texture_width)
                crop_rect.x = 0;
        }

        if (searchCounter >= 2.0f)
        {
            searchCounter = 0;
            wait = true;
        }

        if (waitCounter >= 0.5f)
        {
            waitCounter = 0;
            wait = false;
        }

    }
    else
    {
        frameCounter = 0;
        crop_rect.x = frame_width;
    }
}
