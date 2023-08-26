#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//Texture wrapper class
class Texture
{
    public:
        //Initializes variables
        Texture();

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool load_from_file(std::string path, SDL_Renderer* renderer);

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

        //Gets image dimensions
        int get_width();
        int get_height();

    private:
        //The actual hardware texture
        SDL_Texture* texture;

        //Image dimensions
        int width;
        int height;
};