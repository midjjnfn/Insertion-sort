#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window and renderer
    window = SDL_CreateWindow("SDL Background", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920,1080, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load and render the background image (Assuming "background.jpg" as the image file)
    SDL_Surface* backgroundSurface = SDL_LoadBMP("Screenshot-2023-12-27-022428.bmp");
    if (backgroundSurface == NULL) {
        printf("Unable to load image! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (backgroundTexture == NULL) {
        printf("Unable to create texture! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect backgroundRect = { 0, 0, 1920, 1080 }; // Set position and size of the image
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

    // Update the screen
    SDL_RenderPresent(renderer);

    // Wait for a few seconds before exiting
   SDL_Delay(10000);

    // Clean up resources and quit SDL
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
