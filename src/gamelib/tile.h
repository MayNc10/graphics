#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../lib/texture.h"
#include "token.h"

// Tile Class
class Tile {
    public:
        // Initializes variables
        Tile();

        // Copy Constructor
        Tile(const Tile &other);

        // Deallocates memory
        ~Tile();

        // Gets coordinates
        int get_x();
        int get_y();

        // Sets coordinates
        void set_x(int new_x);
        void set_y(int new_y);
        void set_pos(int new_x, int new_y);

        // Gets height
        int get_height();

        // Sets height
        void set_height(int new_height);

        // Gets token
        Token* get_token();

        // Moves token
        bool move_token(Tile* other);

        // Backing Texture
        Texture texture;

    private:
        // Texture coordinates (move these to texture class?)
        int x;
        int y;

        // Height of tile (?)
        int height;

        // Game token on tile
        Token* token;
};