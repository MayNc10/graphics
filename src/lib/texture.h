#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//Texture wrapper class
class Texture
{
    public:
        // Initializes variables
        Texture();

        // Deallocates memory
        ~Texture();

        // Loads image at specified path
        bool load_from_file(std::string path, SDL_Renderer* renderer);

        // Loads image with color keying
        bool load_with_keying(std::string path, SDL_Renderer* renderer, Uint32* key_ptr = nullptr);

        // Deallocates texture
        void free();

        // Renders texture at given point
        void render(int x, int y, SDL_Renderer* renderer, 
            SDL_Rect* clip = nullptr, SDL_Rect* dest = nullptr);

        // Gets image dimensions
        int get_width();
        int get_height();

        // Gets backing sdl texture
        SDL_Texture* get_texture();

        // Change backing texture
        void set_texture(SDL_Texture* new_texture);

    private:
        // The actual hardware texture
        SDL_Texture* texture;

        // Image dimensions
        int width;
        int height;
};