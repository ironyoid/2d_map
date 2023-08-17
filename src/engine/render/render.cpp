#include <SDL2/SDL.h>
#include "sdl2.h"
#include "render.h"
#include <memory>

using std::cout;
using std::endl;

bool Point2D::operator==(const Point2D &other) const {
    return (x == other.x && y == other.y);
}

bool Line2D::operator==(const Line2D &other) const {
    return (a == other.a && b == other.b);
}

Render::Render(std::string title, uint32_t width, uint32_t height) {
    system = SDL_Init(SDL_INIT_VIDEO);
    if(!system) {
        cout << "SDL subsystem has not been inited!" << endl;
    }
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    if(!window) {
        cout << "SDL window has not been inited!" << endl;
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!render) {
        cout << "SDL render has not been inited!" << endl;
    }
}

void Render::DrawLine(Line2D line, uint32_t thickness, Color color) {
    SDL_Rect rect[] = { { 100, 100, 50, 50 } };
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(render, rect);
}

Render::~Render() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}