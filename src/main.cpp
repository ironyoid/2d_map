#include <SDL2/SDL.h>
#include <iostream>
#include "render.h"
using std::cout;
using std::endl;

int main (int argv, char **args) {
    auto render = new Render("2d_engine", 640, 480);

    SDL_Rect rect[] = {
        { 100, 100, 50, 50 },
    };

    SDL_Event e;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(render->render, 242, 242, 242, 255);
        SDL_RenderClear(render->render);
        SDL_SetRenderDrawColor(render->render, 0, 0, 0, 255);
        SDL_RenderFillRect(render->render, rect);
        SDL_RenderPresent(render->render);
    }

    return 0;
}