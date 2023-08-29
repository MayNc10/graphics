#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>



const std::string BASE_TILE_PATH = "/home/may/tabletop_lancer/media/BasicHexGroundSand.png";

bool init_hexmap(SDL_Renderer* renderer, int window_width, int window_height, int map_radius);