#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

Texture::Texture() {
    texture = nullptr;
    height = -1;
    width = -1;
}

Texture::~Texture() {
    // Free texture if it hasn't been freed yet
    SDL_DestroyTexture(texture);
}

bool Texture::load_from_file(std::string path, SDL_Renderer* renderer) {
    // Make sure we don't lose the old texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        return false;
    } else {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (texture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            return false;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    return true;
}

void Texture::free() {
    SDL_DestroyTexture(texture);
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* dest) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad;
    if (dest) {
        renderQuad = *dest;
    } else {
        renderQuad = { x, y, width, height };
    }

    // Set clip rendering dimensions
    if (clip != nullptr) {
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

SDL_Texture* Texture::get_texture() {
    return texture;
}

void Texture::set_texture(SDL_Texture* new_texture) {
    // Free currently used texture
    SDL_DestroyTexture(texture);
    texture = new_texture;
}

bool Texture::load_with_keying(std::string path, SDL_Renderer* renderer, Uint32* key_ptr) {
    // Make sure we don't lose the old texture
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    // Create an SDL surface with the right pixels
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    Uint32 key;
    if (!key_ptr) {
        key = SDL_MapRGB(surface->format, 255, 255, 255); // White will be keyed out as default
    }
    else {
        key = *key_ptr;
    }

    int result = SDL_SetColorKey(surface, SDL_TRUE, key); // Key out color
    if (result == -1) {
        printf("Error with keying out color!");
        return false;
    }

    // Create texture from modified surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Free surface
    SDL_FreeSurface(surface);

    return true;
}
