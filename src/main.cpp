#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <string>
#include "lib/array.h"
#include "lib/texture.h"
 
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();

// Loads individual image
SDL_Surface* load_surface(std::string path);

// Frees media and shuts down SDL
void close(Array<SDL_Surface*> surfaces, Array<SDL_Texture*> textures);

// Loads individual image as texture
SDL_Texture* load_texture(std::string path);

// The window we'll be rendering to
SDL_Window* WINDOW = NULL;
    
// The surface contained by the window
SDL_Surface* SCREEN_SURFACE = NULL;

// The window renderer
SDL_Renderer* RENDERER = NULL;

int main(int argc, char *argv[]) {
    // Forward declare surfaces
    Texture image_tex = Texture();

    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!image_tex.load_from_file("../media/trump.jpg", RENDERER)) {
            printf("Failed to load media!\n");
        } else {
            // Clear screen
            SDL_RenderClear( RENDERER );

            SDL_Rect clip;
            SDL_GetWindowSize(WINDOW, &clip.w, &clip.h);

            image_tex.render(0, 0, RENDERER, &clip);

            // Update screen
            SDL_RenderPresent( RENDERER );

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

    // Create surfaces array
    SDL_Surface* arr_surfaces[] = {};
    auto surfaces = Array<SDL_Surface*> {arr_surfaces, sizeof(arr_surfaces) / sizeof(arr_surfaces[0])};

    // Create textures array
    SDL_Texture* arr_textures[] = {};
    auto textures = Array<SDL_Texture*> {arr_textures, sizeof(arr_textures) / sizeof(arr_textures[0])};

    // Free resources and close SDL
    close(surfaces, textures);
    
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
        if (WINDOW == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer for window
            RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
            if (RENDERER == NULL) {
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
    SDL_Surface* optimizedSurface = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    else {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, SCREEN_SURFACE->format, 0);
        if(optimizedSurface == NULL) {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

SDL_Texture* load_texture(std::string path) {
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    } else {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(RENDERER, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void close(Array<SDL_Surface*> surfaces, Array<SDL_Texture*> textures) {
    // Free surfaces
    for (int i = 0; i < surfaces.size; i++) {
        SDL_FreeSurface(surfaces.arr[i]);
        surfaces.arr[i] = NULL;
    }

    // Destroy textures
    for (int i = 0; i < textures.size; i++) {
        SDL_DestroyTexture(textures.arr[i]);
        textures.arr[i] = NULL;
    }

    // Destroy window
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    WINDOW = NULL;
    RENDERER = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}