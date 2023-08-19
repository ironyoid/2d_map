#include "grid.hpp"
#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"

using namespace p8g;
using std::cout;
using std::endl;

Grid::Grid(int32_t step, int32_t size_x, int32_t size_y, uint32_t window_width, uint32_t window_height) :
    step(step),
    size_x(size_x),
    size_y(size_y),
    window_width(window_width),
    window_height(window_height) {
    last_position.x = 0;
    last_position.y = 0;
};

void Grid::GenerateGrid(void) {
    uint32_t thick_counter = 0;
    float tmp_thickness = 0;
    for(int32_t x = 0; x < size_x; x += step) {
        if(10 == thick_counter) {
            thick_counter = 0;
            tmp_thickness = 2.0;
        } else {
            tmp_thickness = 1.0;
        }
        grid_x.push_back(Line2D{ x, 0, x, size_y, tmp_thickness });
        thick_counter++;
    }
    thick_counter = 0;
    for(int32_t y = 0; y < size_y; y += step) {
        if(10 == thick_counter) {
            thick_counter = 0;
            tmp_thickness = 2.0;
        } else {
            tmp_thickness = 1.0;
        }
        grid_y.push_back(Line2D{ 0, y, size_x, y, tmp_thickness });
        thick_counter++;
    }
}

// void Grid::UpdateGrid(int32_t delta_x, int32_t delta_y, bool update_x, bool update_y) {
void Grid::UpdateGrid(Point2D new_position) {
    Point2D delta = new_position - last_position;
    for(auto &n : grid_x) {
        n.a.x = n.a.x - delta.x;
        n.b.x = n.b.x - delta.x;
    }
    for(auto &n : grid_y) {
        n.a.y = n.a.y - delta.y;
        n.b.y = n.b.y - delta.y;
    }
    last_position = new_position;
};

void Grid::DrawGrid(void) {
    p8g::stroke(0, 0, 0, 120);
    for(auto n : grid_x) {
        p8g::strokeWeight(n.thickness);
        p8g::line(n.a.x, n.a.y, n.b.x, n.b.y);
    }
    for(auto n : grid_y) {
        p8g::strokeWeight(n.thickness);
        p8g::line(n.a.x, n.a.y, n.b.x, n.b.y);
    }
};

Point2DDistance Grid::Distance(Point2D point, int32_t mouse_x, int32_t mouse_y) {
    int x = (int) point.x - (int) mouse_x;
    int y = (int) point.y - (int) mouse_y;
    Point2DDistance ret{ point, (abs(x) + abs(y)) };
    return ret;
};

std::optional<Point2D> Grid::FindPoint(int32_t mouse_x, int32_t mouse_y, uint32_t threshold, Point2D position) {
    Point2DDistance ret{ 0, 0, step };

    Point2D left_top{ ((mouse_x / step) * step) - position.x % step, ((mouse_y / step) * step) - position.y % step };
    Point2D right_top{ left_top.x + step, left_top.y };
    Point2D left_bottom{ left_top.x, left_top.y + step };
    Point2D right_bottom{ right_top.x, left_top.y + step };

    std::vector<Point2DDistance> vec;
    vec.push_back(Distance(left_top, mouse_x, mouse_y));
    vec.push_back(Distance(right_top, mouse_x, mouse_y));
    vec.push_back(Distance(left_bottom, mouse_x, mouse_y));
    vec.push_back(Distance(right_bottom, mouse_x, mouse_y));

    for(auto n : vec) {
        if(ret.distance > n.distance) {
            ret.a = n.a;
            ret.distance = n.distance;
        }
    }

    if(ret.distance < threshold) {
        return Point2D{ ret.a.x, ret.a.y };
    } else {
        return {};
    }
};