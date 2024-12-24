#include "Acteur.h"

std::vector<std::vector<bool>> Acteur::get_blocked_array(Tile* tile_array, int length)
{
    //SDL_Log("[Acteur<%d>]: get_blocked_array called", index);

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
    //SDL_Log("[Acteur<%d>]: follow_front_rat called", index);

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
    //SDL_Log("[Acteur<%d>]: hold_item_in_mouth called", index);

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
    //SDL_Log("[Acteur<%d>]: Constructor called", index);

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

void Acteur::set_cords_frames(int x, int y, int framesX, int framesY)
{
    //SDL_Log("[Acteur<%d>]: set_cords_frames called with x: %d, y: %d", index, x, y);

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
    //SDL_Log("[Acteur<%d>]: draw called", index);
    Body::draw(renderTarget);
}
void Acteur::use_item()
{
    //SDL_Log("[Acteur<%d>]: use_item called", index);

    if (item_type == 0)
    {
        // Handle item_type 0 if necessary
    }
    else if (item_type == 1)
    {
        saturation = 100;

        holds_item = false;
        item_array[item_hold_id].set_cords(-100, -100);
        item_array[item_hold_id].set_on_map(false);

        //SDL_Log("[Acteur<%d>]: yumm!", index);
        item_type = 0;
    }
}

