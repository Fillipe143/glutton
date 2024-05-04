#include "glutton.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_config.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void throw_error(const char* message);
void throw_sdl_error(const char* message);
void start_loop();

SDL_Window* sdl_window;
SDL_Renderer* sdl_renderer;

void GLN_init_window(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) throw_sdl_error("Failed to initialize the SDL2 library");

    sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (!sdl_window) throw_sdl_error("Failed to create window");

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdl_renderer) throw_sdl_error("Failed to create renderer from window");

    start_loop();
}

void start_loop() {
    bool window_should_close = false;

    while (!window_should_close) {
        SDL_Event event;
        while (SDL_PollEvent(&event) > 0) {
            switch (event.type) {
            case SDL_QUIT:
                window_should_close = true;
                break;
            }
        }
    }
}

void GLN_close_window() {
    SDL_Quit();
}

void throw_error(const char* message) {
    fprintf(stderr, "GLN Error: %s\n", message);
    exit(-1);
}

void throw_sdl_error(const char* message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "SDL2 Error: %s\n", SDL_GetError());
    exit(-1);
}
