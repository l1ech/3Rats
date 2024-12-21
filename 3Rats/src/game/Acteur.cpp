#include "Acteur.h"

std::vector<std::vector<bool>> Acteur::get_blocked_array(Tile* tile_array, int length)
{
    std::cout << "[Acteur<" << index << ">]: get_blocked_array called" << std::endl;

    std::vector<std::vector<bool>> blocked_i(length, std::vector<bool>(4));

    for (int i = 0; i < length; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            blocked_i[i][k] = false;
        }
    }

    struct direction {
        bool right;
        bool left;
        bool up;
        bool down;
    };

    direction block = { false, false, false, false };

    for (int i = 0; i < length; i++)
    {
        if (intersectsWithBody(tile_array[i]))
        {
            if (tile_array[i].get_hight() == 1)
            {
                int delta_x = tile_array[i].get_origin_x() - position_rect.x;
                int delta_y = tile_array[i].get_origin_y() - position_rect.y;

                if (delta_x > 0) block.right = true;
                else if (delta_x < 0) block.left = true;

                if (delta_y > 0) block.down = true;
                else if (delta_y < 0) block.up = true;

                blocked_i[i][0] = block.right;
                blocked_i[i][1] = block.left;
                blocked_i[i][2] = block.down;
                blocked_i[i][3] = block.up;
            }
            else if (tile_array[i].get_hight() == 0)
            {
                block.right = false;
                block.left = false;
                block.down = false;
                block.up = false;
            }
        }
    }
    return blocked_i;
}

void Acteur::follow_front_rat(int rat_x, int rat_y, int front_rat_x, int front_rat_y, block_direction direction, float delta, Acteur& front_rat)
{
    std::cout << "[Acteur<" << index << ">]: follow_front_rat called" << std::endl;

    if (rat_y > front_rat_y && !direction.up)
    {
        position_rect.y -= moveSpeed * delta;
        crop_rect.y = frame_height * 3;
        current_direction = 0;
    }
    else if (rat_y < front_rat_y && !direction.down)
    {
        position_rect.y += moveSpeed * delta;
        crop_rect.y = 0;
        current_direction = 1;
    }
    else if (rat_x > front_rat_x && !direction.left)
    {
        position_rect.x -= moveSpeed * delta;
        crop_rect.y = frame_height;
        current_direction = 2;
    }
    else if (rat_x < front_rat_x && !direction.right)
    {
        position_rect.x += moveSpeed * delta;
        crop_rect.y = frame_height * 2;
        current_direction = 3;
    }
    else
    {
        current_direction = front_rat.GetDirection();
    }

    if (current_direction == 0) crop_rect.y = frame_height * 3;
    if (current_direction == 1) crop_rect.y = 0;
    if (current_direction == 2) crop_rect.y = frame_height;
    if (current_direction == 3) crop_rect.y = frame_height * 2;
}

void Acteur::hold_item_in_mouth(Item& item)
{
    std::cout << "[Acteur<" << index << ">]: hold_item_in_mouth called" << std::endl;

    int offset = 14;

    if (current_direction == 0)
    {
        item.set_cords(get_origin_x() - 24, get_origin_y() - 32 - offset);
    }
    else if (current_direction == 1)
    {
        item.set_cords(get_origin_x() - 24, get_origin_y() - 32 + offset);
    }
    else if (current_direction == 2)
    {
        item.set_cords(get_origin_x() - 24 - offset, get_origin_y() - 32);
    }
    else if (current_direction == 3)
    {
        item.set_cords(get_origin_x() - 24 + offset, get_origin_y() - 32);
    }
}

Acteur::Acteur()
{
    std::cout << "[Acteur<" << index << ">]: Constructor called" << std::endl;

    dead = false;
    item_type = 0;

    saturation = 100;

    file_path = Texture_Constants::META_TEXTURE;
    
    item_search_id = 0;
    has_goal = false;

    is_moving = false;

    keys[0] = SDL_SCANCODE_W;
    keys[1] = SDL_SCANCODE_S;
    keys[2] = SDL_SCANCODE_A;
    keys[3] = SDL_SCANCODE_D;

    moveSpeed = 200.0f;

    wait = false;

    searchCounter = rand() % 100;
    searchCounter /= 100.0f;
}

Acteur::~Acteur()
{
    std::cout << "[Acteur<" << index << ">]: Destructor called" << std::endl;
    SDL_DestroyTexture(texture);
}

void Acteur::set_cords_frames(int x, int y, int framesX, int framesY)
{
    std::cout << "[Acteur<" << index << ">]: set_cords_frames called with x: " << x << ", y: " << y << std::endl;

    position_rect.x = x;
    position_rect.y = y;

    texture_width = crop_rect.w;

    crop_rect.w /= framesX;
    crop_rect.h /= framesY;

    frame_width = position_rect.w = crop_rect.w;
    frame_height = position_rect.h = crop_rect.h;

    origin_x = frame_width / 2;
    origin_y = frame_height / 2;

    radius = frame_width / 2;
}

void Acteur::draw(SDL_Renderer *renderTarget) const
{
	std::cout << std::endl;
    std::cout << "[Acteur<" << index << ">]: draw called" << std::endl;
    Body::draw(renderTarget);
}

void Acteur::Update(float delta, const Uint8 *keyState, int mode, Acteur &front_rat)
{
    std::cout << "[Acteur<" << index << ">]: Update called with delta: " << delta << std::endl;

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

void Acteur::use_item()
{
    std::cout << "[Acteur<" << index << ">]: use_item called" << std::endl;

    if (item_type == 0)
    {

    }
    else if (item_type == 1)
    {
        saturation = 100;

        holds_item = false;
        item_array[item_hold_id].set_cords(-100, -100);
        item_array[item_hold_id].set_on_map(false);

        std::cout << "[Acteur<" << index << ">]: yumm!" << std::endl;
        item_type = 0;
    }
}
