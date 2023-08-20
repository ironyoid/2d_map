#include <iostream>
#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"
#include "grid.hpp"
#include <cmath>

using namespace p8g;
using std::cout;
using std::endl;
using std::vector;

#define WINDOW_WIDTH   (500U)
#define WINDOW_HEIGHT  (500U)
#define GRID_STEP      (20U)
#define GRID_THRESHOLD (20U)

typedef enum {
    eDrawSate_Idle = 0,
    eDrawSate_Start = 1,
    eDrawState_Proccess = 2,
} eDrawStete_t;

class Draw
{
   public:
    static Grid *grid;
    static Point2D start_point;
    static Point2D end_point;
    static uint32_t threshold;
    static eDrawStete_t draw_state;
    static vector<Line2D> lines;
    static Point2D position;
    static Point2D mouse;
    static float scale;
    static bool is_right_button_pressed;
    static bool is_ctrl_pressed;
    static const int LEFT_BUTTON = 0;
    static const int RIGHT_BUTTON = 1;
    static const int CTRL_KEY = 343;
    static const int Z_KEY = 90;
    static const int RIGHT_ARROW_KEY = 262;
    static const int LEFT_ARROW_KEY = 263;
    static const int UP_ARROW_KEY = 265;
    static const int DOWN_ARROW_KEY = 264;
    static const int P_KEY = 80;

    static void Init (uint32_t width,
                      uint32_t height,
                      uint32_t window_width,
                      uint32_t window_height,
                      uint32_t step,
                      uint32_t _threshold) {
        scale = 0.0;
        draw_state = eDrawSate_Start;
        threshold = _threshold;
        grid = new Grid(step, width, height, window_width, window_height);
        grid->GenerateGrid();
        start_point.x = 10;
    }

    static int32_t CheckBoundaries (int32_t val, int32_t delta) {
        int32_t ret = 0;
        if(val - delta < 0) {
            ret = 0;
        } else if((val - delta >= 0) && (val - delta) <= (grid->size_x - grid->window_width)) {
            ret = val - delta;
        } else {
            ret = grid->size_x - grid->window_width;
        }
        return ret;
    }

    static void DrawTask (void) {
        background(250);
        grid->DrawGrid();
        auto point = grid->FindPoint(mouseX, mouseY, threshold, position);
        grid->UpdateGrid(position, (int32_t) scale);
        p8g::strokeWeight(10.0);
        p8g::stroke(0, 255, 0, 200);
        if(point) {
            p8g::point(point.value().x, point.value().y);
        }
        p8g::strokeWeight(2.5);
        p8g::stroke(0, 0, 0, 255);
        for(auto n : lines) {
            p8g::line(n.a.x - position.x, n.a.y - position.y, n.b.x - position.x, n.b.y - position.y);
        }
        switch(draw_state) {
            case eDrawSate_Idle:
                break;
            case eDrawSate_Start:
                break;
            case eDrawState_Proccess:
                p8g::line(start_point.x - position.x, start_point.y - position.y, mouseX, mouseY);
                break;
        }
    };

    static void KeyPressed () {
        if(CTRL_KEY == keyCode) {
            is_ctrl_pressed = true;
        }
        if((Z_KEY == keyCode) && (true == is_ctrl_pressed)) {
            if(!lines.empty()) {
                lines.pop_back();
            }
        }
    };

    static void KeyReleased () {
        cout << "key = " << keyCode << endl;
        if(CTRL_KEY == keyCode) {
            is_ctrl_pressed = false;
        }
        if(P_KEY == keyCode) {
            for(auto n : lines) {
                cout << "(" << n.a.x << ", " << n.a.y << ")"
                     << " "
                     << "(" << n.b.x << ", " << n.b.y << ")" << endl;
            }
        }
        if(RIGHT_ARROW_KEY == keyCode) {
            position.x = CheckBoundaries(position.x, -1);
            position.y = CheckBoundaries(position.y, 0);
            grid->UpdateGrid(position);
        }
        if(LEFT_ARROW_KEY == keyCode) {
            position.x = CheckBoundaries(position.x, 1);
            position.y = CheckBoundaries(position.y, 0);
            grid->UpdateGrid(position);
        }
        if(UP_ARROW_KEY == keyCode) {
            position.x = CheckBoundaries(position.x, 0);
            position.y = CheckBoundaries(position.y, 1);
            grid->UpdateGrid(position);
        }
        if(DOWN_ARROW_KEY == keyCode) {
            position.x = CheckBoundaries(position.x, 0);
            position.y = CheckBoundaries(position.y, -1);
            grid->UpdateGrid(position);
        }
    };

    static void MouseReleased () {
        if(LEFT_BUTTON == mouseButton) {
            auto point = grid->FindPoint(mouseX, mouseY, threshold, position);
            switch(draw_state) {
                case eDrawSate_Idle:
                    draw_state = eDrawSate_Start;
                case eDrawSate_Start:
                    if(point) {
                        start_point.x = point.value().x + position.x;
                        start_point.y = point.value().y + position.y;
                    } else {
                        start_point.x = mouseX + position.x;
                        start_point.y = mouseY + position.y;
                    }
                    draw_state = eDrawState_Proccess;
                    break;
                case eDrawState_Proccess:
                    if(point) {
                        end_point.x = point.value().x + position.x;
                        end_point.y = point.value().y + position.y;
                    } else {
                        end_point.x = mouseX + position.x;
                        end_point.y = mouseY + position.y;
                    }
                    lines.push_back(Line2D{ start_point.x, start_point.y, end_point.x, end_point.y });
                    draw_state = eDrawSate_Idle;
                    break;
            }
        }
        if(RIGHT_BUTTON == mouseButton) {
            is_right_button_pressed = false;
            // draw_state = eDrawSate_Idle;
        }
    };

    static void MouseMoved () {
        if(true == is_right_button_pressed) {
            int32_t delta_x = mouse.x - mouseX;
            int32_t delta_y = mouse.y - mouseY;
            position.x = CheckBoundaries(position.x, -delta_x);
            position.y = CheckBoundaries(position.y, -delta_y);
            mouse.x = mouseX;
            mouse.y = mouseY;
        }
    };
    static void MousePressed () {
        if(RIGHT_BUTTON == mouseButton) {
            mouse.x = mouseX;
            mouse.y = mouseY;
            is_right_button_pressed = true;
        }
    };
    static void MouseWheel (float delta) {
        scale = round((scale + delta));
        cout << "scale = " << scale << " key = " << mouseButton << endl;
    };
};

Grid *Draw::grid;
Point2D Draw::start_point;
Point2D Draw::end_point;
Point2D Draw::position;
uint32_t Draw::threshold;
eDrawStete_t Draw::draw_state;
vector<Line2D> Draw::lines;
bool Draw::is_ctrl_pressed;
bool Draw::is_right_button_pressed;
Point2D Draw::mouse;
float Draw::scale;

int main () {
    Draw::Init(WINDOW_WIDTH * 2, WINDOW_HEIGHT * 2, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_STEP, GRID_THRESHOLD);
    Draw test{};
    RunArgs run_args{ WINDOW_WIDTH, WINDOW_HEIGHT, "2d_engine", false };
    p8g::_run(run_args,
              &Draw::DrawTask,
              &Draw::KeyPressed,
              &Draw::KeyReleased,
              &Draw::MouseMoved,
              &Draw::MousePressed,
              &Draw::MouseReleased,
              &Draw::MouseWheel);
}