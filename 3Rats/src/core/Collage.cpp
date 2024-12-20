#include "Collage.h"


Collage::Collage()
{
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/fonts/sans/sans.ttf");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/ui_textures/fade.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/meta_textures/place_holder.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/mango.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/fridolin.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/rat_textures/remy.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/npc_textures/entity.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/images/backgound.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/empty.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/ui_textures/clock_frame.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_door.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_wall.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/walk_way_shadow_horizontal.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/walk_way_shadow_vertical.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/ground.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/maze_hole.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/maze_textures/wooden_floor.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/interactable/test.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/item_textures/mushroom.png");
    paths.push_back("/Users/c0d3_cru5h/Projekte/Code/3Rats/3Rats/assets/textures/item_textures/place_holder.png");

}

Collage::~Collage()
{
}

// Returns the path of the texture at the given position `i` in the `paths` vector.
// The mapping of indices to textures is as follows:
// 0: Font - sans.ttf
// 1: UI Texture - fade.png
// 2: Meta Texture - place_holder.png
// 3: Rat Texture - mango.png
// 4: Rat Texture - fridolin.png
// 5: Rat Texture - remy.png
// 6: NPC Texture - entity.png
// 7: Background - backgound.png
// 8: Empty Texture - empty.png
// 9: clock_frame.png
// 10: maze_door.png
// 11: maze_wall.png
// 12: walk_way_shadow_horizontal.png
// 13: walk_way_shadow_vertical.png
// 14: ground.png
// 15: maze_hole.png
// 16: wooden_floor.png
// 17: test.png
// 18: mushroom.png"
// 19: place_holder.png
std::string Collage::get_path(int i)
{
    if (i >= 0 && i < paths.size()) {
        // Debug: Confirm the path retrieval was successful
        //std::cout << "Debug: Successfully fetched path at index " << i << ": " << paths.at(i) << std::endl;
        return paths.at(i);
    } else {
        // Debug: Report if the index is invalid
        //std::cout << "Debug: Index " << i << " is out of range, returning empty string." << std::endl;
        return "";
    }
}