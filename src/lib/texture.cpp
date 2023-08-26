#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

Texture::Texture() {
    texture = NULL;
    height = -1;
    width = -1;
}

Texture::~Texture() {
    // Free texture if it hasn't been freed yet
    SDL_DestroyTexture(texture);
}

bool Texture::load_from_file(std::string path, SDL_Renderer* renderer) {
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    } else {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    return true;
}

void Texture::free() {
    SDL_DestroyTexture(texture);
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };

    // Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(renderer, texture, clip, &renderQuad );
}

int Texture::get_width() {
    return width;
}

int Texture::get_height() {
    return height;
}