#pragma once
#include <_types/_uint32_t.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include "quadtree.hpp"
#include <optional>
#include <sys/types.h>
#include <vector>

struct Point2DDistance {
    Point2D a;
    int32_t distance;
};

class Grid
{
    int32_t step;
    std::vector<Line2D> grid_x;
    std::vector<Line2D> grid_y;

   public:
    int32_t size_x;
    int32_t size_y;
    uint32_t window_width;
    uint32_t window_height;
    Point2D last_position;
    Grid(int32_t step, int32_t size_x, int32_t size_y, uint32_t window_width, uint32_t window_height);
    void GenerateGrid (void);
    void DrawGrid (void);
    // void UpdateGrid (int32_t delta_x, int32_t delta_y, bool update_x, bool update_y);
    void UpdateGrid (Point2D new_position);
    std::optional<Point2D> FindPoint (int32_t mouse_x, int32_t mouse_y, uint32_t threshold, Point2D position);
    Point2DDistance Distance (Point2D point, int32_t mouse_x, int32_t mouse_y);
};