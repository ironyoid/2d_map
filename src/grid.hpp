#pragma once
#include <iostream>
#include <string>
#include <stdint.h>
#include "quadtree.hpp"

struct Point2DDistance {
    Point2D a;
    uint32_t distance;
};

class Grid
{
    uint32_t step;
    uint32_t size_x;
    uint32_t size_y;
    float thickness;

   public:
    Grid(uint32_t step, uint32_t size_x, uint32_t size_y, float thickness);
    void DrawGrid ();
    Point2D FindPoint (uint32_t mouse_x, uint32_t mouse_y);
    Point2DDistance Distance (Point2D point, uint32_t mouse_x, uint32_t mouse_y);
};