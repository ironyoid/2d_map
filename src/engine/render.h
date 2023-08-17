#pragma once
#include "stdint.h"
#include <iostream>
#include "sdl2.h"
#include <string>
#include <functional>

struct Point2D {
    int32_t x;
    int32_t y;
    bool operator==(const Point2D &other) const;
};

struct Line2D {
    Point2D a;
    Point2D b;

    bool operator==(const Line2D &other) const;
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

class Render
{
   private:
    int system;
    SDL_Window *window;

   public:
    SDL_Renderer *render;
    Render(std::string title, uint32_t width, uint32_t height);
    void DrawLine (Line2D line, uint32_t thickness, Color color);
    ~Render();
};