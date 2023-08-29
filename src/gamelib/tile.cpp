#include "tile.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../lib/texture.h"
#include "token.h"

Tile::Tile() {
    x = 0;
    y = 0;

    height = 0;

    token = nullptr;

    texture = Texture();
}

// NOTE: Doesn't copy texture or token (Should we?)
Tile::Tile(const Tile &other) {
    x = other.x;
    y = other.y;
    height = other.height;
    
    token = nullptr;
}

// TODO: Do we need to deallocate the texture? Does this leak memory?
Tile::~Tile() {
    // Do we need to deallocate the token?
    token = nullptr;
}

int Tile::get_x() {
    return x;
}

int Tile::get_y() {
    return y;
}

void Tile::set_x(int new_x) {
    x = new_x;
}

void Tile::set_y(int new_y) {
    y = new_y;
}

void Tile::set_pos(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}

int Tile::get_height() {
    return height;
}

void Tile::set_height(int new_height) {
    height = new_height;
}

Token* Tile::get_token() {
    return token;
}

bool Tile::move_token(Tile* other) {
    if (other->token) {
        return false; // Should have no token on it
    } 
    other->token = token;
    token = nullptr;
    return true;
}
