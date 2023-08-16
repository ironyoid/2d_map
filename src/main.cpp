#include <SDL2/SDL.h>
#include <iostream>
#include "sdl2.h"

auto main () -> int {
    using std::cerr;
    using std::endl;
    SDL_Window *win;
    SDL_Renderer *rdr;
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Rect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    rdr = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rect[] = {
        { 100, 100, 50, 50 },
        { 101, 101, 48, 48 },
        { 102, 102, 46, 46 },
        { 103, 103, 44, 44 },
    };

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(rdr, 242, 242, 242, 255);
        SDL_RenderClear(rdr);
        SDL_SetRenderDrawColor(rdr, 0, 0, 0, 255);
        SDL_RenderDrawRect(rdr, rect);
        SDL_RenderPresent(rdr);
    }

    return 0;
}