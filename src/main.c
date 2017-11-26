#include "SDL.h"
#include <stdio.h>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
#endif

// This example mostly based off of
// http://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-1-hello-world

int quit = 0;

void main_loop() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = 1;
        }
    }
}

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    #ifndef __EMSCRIPTEN__
        SDL_SetWindowBordered(window, 0);
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    #endif

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL){
	    SDL_DestroyWindow(window);
	    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
	    SDL_Quit();
	    return 1;
    }

    char *imagePath = "resources/hello.bmp";
    SDL_Surface *bmp = SDL_LoadBMP(imagePath);
    if (bmp == NULL) {
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
	    SDL_Quit();
	    return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    if (texture == NULL) {
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
	    SDL_Quit();
	    return 1;
    }

	SDL_RenderClear(renderer);
	//Draw the texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	//Update the screen
	SDL_RenderPresent(renderer);

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(main_loop, 0, 1);
    #else
        while(quit == 0) main_loop();
    #endif

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}