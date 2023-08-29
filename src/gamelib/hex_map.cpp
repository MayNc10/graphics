#include "hex_map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#include "tile.h"
#include "../lib/texture.h"

int num_hex_per_radius(int radius);

bool init_hexmap(SDL_Renderer* renderer, int window_width, int window_height, int map_radius) {
    // Create the progenitor hex tile
    Tile copy_tile = Tile();
    // Create base texture TODO: Create a global array of textures or smth (and def save this one)
    
    Texture base_texture = Texture();
    
    if (!base_texture.load_from_file(BASE_TILE_PATH, renderer)) {
        return false;
    }
    copy_tile.texture = base_texture;

    // Create list of hex tiles
    std::vector<Tile> tiles;
    tiles.reserve(num_hex_per_radius(map_radius));


    // The hexes are actually just rects with transparent parts, so to plot at the center we do some simple math
    Tile tile = copy_tile;
    tile.texture = base_texture;

    int hex_0_x = window_width / 2 - tile.texture.get_width();
    int hex_0_y = window_height / 2 - tile.texture.get_height();

    tile.set_pos(hex_0_x, hex_0_y);

    // Render first tile
    tile.texture.render(tile.get_x(), tile.get_y(), renderer); // TODO: Add a render function to tile
    
    return true;
}

// Recursive function to help predict how many hexes there should be
int num_hex_per_radius(int radius) {
    // Base case
    if (radius == 1) { return 1; }
    return num_hex_per_radius(radius - 1) + 6 * (radius - 1);
}


