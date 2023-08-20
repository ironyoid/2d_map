#include "grid.hpp"
#include <iostream>
#include <sys/_types/_int32_t.h>
#include <utility>
#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"
#include <cmath>
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

std::pair<std::vector<Line2D>, std::vector<Line2D>> Grid::GenerateGrid(void) {
    uint32_t thick_counter = 0;
    float tmp_thickness = 0;
    std::vector<Line2D> grid_x;
    std::vector<Line2D> grid_y;
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
    return std::make_pair(grid_x, grid_y);
}

// void Grid::UpdateGrid(Point2D new_position, int32_t scale) {
//     Point2D delta = new_position - last_position;
//     for(auto &n : grid_x) {
//         n.a.x = n.a.x - delta.x;
//         n.b.x = n.b.x - delta.x;
//     }
//     for(auto &n : grid_y) {
//         n.a.y = n.a.y - delta.y;
//         n.b.y = n.b.y - delta.y;
//     }
//     last_position = new_position;
// };

// void Grid::DrawGrid(void) {
//     p8g::stroke(0, 0, 0, 120);
//     for(auto n : grid_x) {
//         p8g::strokeWeight(n.thickness);
//         p8g::line(n.a.x, n.a.y, n.b.x, n.b.y);
//     }
//     for(auto n : grid_y) {
//         p8g::strokeWeight(n.thickness);
//         p8g::line(n.a.x, n.a.y, n.b.x, n.b.y);
//     }
// };

Point2DDistance Grid::Distance(Point2D point, int32_t mouse_x, int32_t mouse_y) {
    float x = point.x - mouse_x;
    float y = point.y - mouse_y;
    Point2DDistance ret{ point, (int32_t) (abs(x) + abs(y)) };
    return ret;
};

std::optional<Point2D> Grid::FindPoint(int32_t mouse_x,
                                       int32_t mouse_y,
                                       uint32_t threshold,
                                       Point2D position,
                                       float scale) {
    int32_t step_tmp = round(static_cast<float>(step) * scale);
    cout << "step = " << step_tmp << endl;
    Point2DDistance ret{ 0, 0, step_tmp };
    Point2D left_top{ ((mouse_x / step_tmp) * step_tmp) - ((int32_t) position.x) % step_tmp,
                      ((mouse_y / step_tmp) * step_tmp) - ((int32_t) position.y) % step_tmp };
    Point2D right_top{ left_top.x + step_tmp, left_top.y };
    Point2D left_bottom{ left_top.x, left_top.y + step_tmp };
    Point2D right_bottom{ right_top.x, left_top.y + step_tmp };

    std::vector<Point2DDistance> vec;
    vec.push_back(Distance(left_top, mouse_x, mouse_y));
    vec.push_back(Distance(right_top, mouse_x, mouse_y));
    vec.push_back(Distance(left_bottom, mouse_x, mouse_y));
    vec.push_back(Distance(right_bottom, mouse_x, mouse_y));

    for(auto n : vec) {
        cout << n.distance << " ";
        if(ret.distance > n.distance) {
            ret.a = n.a;
            ret.distance = n.distance;
        }
    }
    ret.a.Print();
    cout << " ";
    cout << ret.distance << " ";
    if(ret.distance < threshold) {
        return Point2D{ (int32_t) (ret.a.x), (int32_t) (ret.a.y) };
    } else {
        return {};
    }
};