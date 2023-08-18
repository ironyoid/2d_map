#include "grid.hpp"
#include <vector>
#include "p8g.hpp"

using namespace p8g;
using std::cout;
using std::endl;

Grid::Grid(uint32_t step, uint32_t size_x, uint32_t size_y, float thickness) :
    step(step),
    size_x(size_x),
    size_y(size_y),
    thickness(thickness){};

void Grid::DrawGrid() {
    p8g::strokeWeight(thickness);
    for(uint32_t x = 0; x < size_x; x += step) {
        p8g::line(x, 0, x, size_y);
    }
    for(uint32_t y = 0; y < size_y; y += step) {
        p8g::line(0, y, size_x, y);
    }
};

Point2DDistance Grid::Distance(Point2D point, uint32_t mouse_x, uint32_t mouse_y) {
    int x = (int) point.x - (int) mouse_x;
    int y = (int) point.y - (int) mouse_y;
    Point2DDistance ret{ point, ((uint32_t) abs(x) + (uint32_t) abs(y)) };
    return ret;
};

Point2D Grid::FindPoint(uint32_t mouse_x, uint32_t mouse_y) {
    Point2DDistance ret{ 0, 0, step };

    Point2D left_top{ (mouse_x / step) * step, (mouse_y / step) * step };
    Point2D right_top{ left_top.x + step, left_top.y };
    Point2D left_bottom{ left_top.x, left_top.y + step };
    Point2D right_bottom{ left_top.x + step, left_top.y + step };

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
    cout << endl;
    return ret.a;
};