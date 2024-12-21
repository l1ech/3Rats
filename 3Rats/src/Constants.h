// constants.h
#pragma once

#include <SDL.h>

namespace Init_Constants {
    const int TEXT_SIZE = 24;
    const SDL_Color TEXT_COLOR = {255, 0, 0};

    // Fade Constants
    const int FADE_TEXT_X = 999;
    const int FADE_TEXT_Y = 999;
    const int FADE_X = 100;
    const int FADE_Y = 100;
    const int FADE_WIDTH = 200;
    const int FADE_HEIGHT = 90;

    // Clock Constants
    const int CLOCK_X = 400;
    const int CLOCK_Y = 320;
    const int CLOCK_WIDTH = 200;
    const int CLOCK_HEIGHT = 90;

    const int MAX_ITEMS = 100;
    const int NUM_TEXTURES = 10;
    const int ITEM_INITIAL_X = 0;
    const int ITEM_INITIAL_Y = 0;
    const int OFFSET_X = 10;
    const int OFFSET_Y = 10;
    const int TILE_INITIAL_X = 0;
    const int TILE_INITIAL_Y = 0;
    const int PLAYER_FRAME_WIDTH = 64;
    const int PLAYER_FRAME_HEIGHT = 64;
    const int PLAYER_FRAME_ROWS = 4;
    const int PLAYER_FRAME_COLUMNS = 4;

    // Entity Constants
    const int ENTITY_INITIAL_X = 0;
    const int ENTITY_INITIAL_Y = 0;
    const int ENTITY_FRAME_ROWS = 4;
    const int ENTITY_FRAME_COLUMNS = 4;
}

namespace Map_Constans 
{
    const int MAX_RECURSION_DEPTH = 10000000;
    const int TILE_SIZE = 64; // Tile size constant    

    enum Direction
    {
        RIGHT = 3,
        LEFT = 4,
        UP = 5,
        DOWN = 6,
        ERROR_DIRECTION = 20
    };

    const int EXIT = 0;
    const int WALL = 1;
    const int ENTRY = 2;
    const int EXIT_ALT = 13;
    const int RIGHT_HORIZONTAL_PATH = 3;
    const int LEFT_HORIZONTAL_PATH = 4;
    const int UP_VERTICAL_PATH = 5;
    const int DOWN_VERTICAL_PATH = 6;
    const int UNKNOWN_VALUE = 9;
}

namespace Texture_Constants {
    const std::string FONT = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/fonts/sans/sans.ttf";
    const std::string UI_TEXTURE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/ui_textures/fade.png";
    const std::string META_TEXTURE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/meta_textures/place_holder.png";
    const std::string RAT_TEXTURE_MANGO = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/mango.png";
    const std::string RAT_TEXTURE_FRIDOLIN = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/fridolin.png";
    const std::string RAT_TEXTURE_REMY = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/remy.png";
    const std::string NPC_TEXTURE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/npc_textures/entity.png";
    const std::string BACKGROUND = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/images/backgound.png";
    const std::string EMPTY_TEXTURE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/empty.png";
    const std::string CLOCK_FRAME = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/ui_textures/clock_frame.png";
    const std::string MAZE_DOOR = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_door.png";
    const std::string MAZE_WALL = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_wall.png";
    const std::string WALK_WAY_SHADOW_HORIZONTAL = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/walk_way_shadow_horizontal.png";
    const std::string WALK_WAY_SHADOW_VERTICAL = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/walk_way_shadow_vertical.png";
    const std::string GROUND = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/ground.png";
    const std::string MAZE_HOLE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_hole.png";
    const std::string WOODEN_FLOOR = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/wooden_floor.png";
    const std::string INTERACTABLE = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/interactable/test.png";
    const std::string MUSHROOM = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/item_textures/mushroom.png";
    const std::string PLACE_HOLDER = "/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/item_textures/place_holder.png";
}
