#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <string>
#include "lib/array.h"
#include "lib/texture.h"
#include "gamelib/tile.h"
#include "gamelib/hex_map.h"
 
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads individual image
SDL_Surface* load_surface(std::string path);

// Frees media and shuts down SDL
void close();

// Loads individual image as texture
SDL_Texture* load_texture(std::string path);

// The window we'll be rendering to
SDL_Window* WINDOW = nullptr;
    
// The surface contained by the window
SDL_Surface* SCREEN_SURFACE = nullptr;

// The window renderer
SDL_Renderer* RENDERER = nullptr;

int main(int argc, char *argv[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else { 
        // Load media
        if (!init_hexmap(RENDERER, SCREEN_WIDTH, SCREEN_HEIGHT, 1)) { 
            printf("Failed to load media!\n");
        } else {
            // Update screen
            SDL_RenderPresent(RENDERER);

            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            while (!quit) {
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    // User presses a key
                    else if (e.type == SDL_KEYDOWN) {

                    }
                }
            }
        }
    }
    // Free resources and close SDL
    close();
    
    return 0;
}

bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Create window
        WINDOW = SDL_CreateWindow("SDL Tutorial", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (WINDOW == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer for window
            RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
            if (RENDERER == nullptr) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(RENDERER, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Surface* load_surface(std::string path) {
    // The final optimized image
    SDL_Surface* optimizedSurface = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    else {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, SCREEN_SURFACE->format, 0);
        if(optimizedSurface == nullptr) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture* load_texture(std::string path) {
    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(RENDERER, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void close() {
    // Destroy window
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    WINDOW = nullptr;
    RENDERER = nullptr;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}