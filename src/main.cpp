#include <iostream>
#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"
#include "grid.hpp"

using namespace p8g;
using std::cout;
using std::endl;
using std::vector;

#define WINDOW_WIDTH   (800U)
#define WINDOW_HEIGHT  (800U)
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
    static bool is_ctrl_pressed;
    static const int LEFT_BUTTON = 0;
    static const int RIGHT_BUTTON = 1;
    static const int CTRL_KEY = 343;
    static const int Z_KEY = 90;

    static void Init (uint32_t width, uint32_t height, uint32_t step, uint32_t _threshold) {
        draw_state = eDrawSate_Start;
        threshold = _threshold;
        grid = new Grid(step, width, height);
        start_point.x = 10;
    }

    static void DrawTask (void) {
        background(250);
        grid->DrawGrid();
        auto point = grid->FindPoint(mouseX, mouseY, threshold);
        p8g::strokeWeight(10.0);
        p8g::stroke(0, 255, 0, 200);
        if(point) {
            p8g::point(point.value().x, point.value().y);
        }
        p8g::strokeWeight(2.5);
        p8g::stroke(0, 0, 0, 255);
        for(auto n : lines) {
            p8g::line(n.a.x, n.a.y, n.b.x, n.b.y);
        }
        switch(draw_state) {
            case eDrawSate_Idle:
                break;
            case eDrawSate_Start:
                break;
            case eDrawState_Proccess:
                p8g::line(start_point.x, start_point.y, mouseX, mouseY);
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
        if(CTRL_KEY == keyCode) {
            is_ctrl_pressed = false;
        }
    };

    static void MouseReleased () {
        if(LEFT_BUTTON == mouseButton) {
            auto point = grid->FindPoint(mouseX, mouseY, threshold);
            switch(draw_state) {
                case eDrawSate_Idle:
                    draw_state = eDrawSate_Start;
                case eDrawSate_Start:
                    if(point) {
                        start_point = point.value();
                    } else {
                        start_point.x = (uint32_t) mouseX;
                        start_point.y = (uint32_t) mouseY;
                    }
                    draw_state = eDrawState_Proccess;
                    break;
                case eDrawState_Proccess:
                    if(point) {
                        end_point = point.value();
                    } else {
                        end_point.x = (uint32_t) mouseX;
                        end_point.y = (uint32_t) mouseY;
                    }
                    lines.push_back(Line2D{ start_point.x, start_point.y, end_point.x, end_point.y });
                    draw_state = eDrawSate_Idle;
                    break;
            }
        } else if(RIGHT_BUTTON == mouseButton) {
            draw_state = eDrawSate_Idle;
        }
    };

    static void MouseMoved (){};
    static void MousePressed (){};
    static void MouseWheel (float delta){};
};

Grid *Draw::grid;
Point2D Draw::start_point;
Point2D Draw::end_point;
uint32_t Draw::threshold;
eDrawStete_t Draw::draw_state;
vector<Line2D> Draw::lines;
bool Draw::is_ctrl_pressed;

int main () {
    Draw::Init(WINDOW_WIDTH, WINDOW_HEIGHT, GRID_STEP, GRID_THRESHOLD);
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