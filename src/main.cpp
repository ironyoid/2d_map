#include <iostream>
#include <vector>
#include "p8g.hpp"
#include "parser.hpp"
#include "points.hpp"
#include "grid.hpp"
#include <cmath>

using namespace p8g;
using std::cout;
using std::endl;
using std::vector;

#define WINDOW_WIDTH   (1000U)
#define WINDOW_HEIGHT  (1000U)
#define GRID_STEP      (20U)
#define GRID_THRESHOLD (20U)

typedef enum {
    eDrawSate_Idle = 0,
    eDrawSate_Start = 1,
    eDrawState_Proccess = 2,
} eDrawStete_t;

typedef enum {
    eLeft_Button = 0,
    eRight_Button = 1,
} eMouseButtons_t;

typedef enum {
#ifdef WINDOWS_BUILD
    eCtrl_Key = 341,
#else
    eCtrlKey = 343,
#endif
    eZ_Key = 90,
    eRightArrow_Key = 262,
    eLeftArrow_Key = 263,
    eUpArrow_Key = 265,
    eDownArrow_Key = 264,
    eP_Key = 80,
    eR_Key = 82,
    ePlus_Key = 61,
    eMinus_key = 45,
} eKeyboardKeys_t;

class Draw
{
   public:
    static Grid *grid;
    static Parser *parser;
    static Point2D start_point;
    static Point2D end_point;
    static uint32_t threshold;
    static uint32_t window_width;
    static uint32_t window_height;
    static eDrawStete_t draw_state;
    static vector<Line2D> lines;
    static Point2D position;
    static Point2D mouse;
    static Point2D robot_point;
    static float scale;
    static bool is_right_button_pressed;
    static bool is_ctrl_pressed;
    constexpr static float LINE_THICKNESS = 4.0;

    static void Init (uint32_t width,
                      uint32_t height,
                      uint32_t _window_width,
                      uint32_t _window_height,
                      uint32_t step,
                      uint32_t _threshold,
                      std::string path) {
        window_width = _window_width;
        window_height = _window_height;
        robot_point.x = 0;
        robot_point.y = 0;
        scale = 1.0;
        draw_state = eDrawSate_Start;
        threshold = _threshold;
        parser = new Parser(path);
        grid = new Grid(step, width, height, _window_width, _window_height);
        grid->GenerateGrid();
        start_point.x = 10;
    }

    static void UpdateScale (float new_scale) {
        if(scale + new_scale >= 1.0) {
            scale = scale + new_scale;
        } else {
            scale = 1;
        }
        cout << "scale = " << scale << endl;
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

    static void DrawLines (vector<Line2D> lines, Point2D _position) {
        for(auto n : lines) {
            p8g::strokeWeight(n.thickness);
            p8g::line(n.a.x - _position.x, n.a.y - _position.y, n.b.x - _position.x, n.b.y - _position.y);
        }
    }

    static void DrawTask (void) {
        background(250);
        auto point = grid->FindPoint(mouseX, mouseY, threshold, position, scale);
        p8g::strokeWeight(10.0);
        p8g::stroke(0, 255, 0, 200);
        p8g::applyMatrix(1.0, 0, 0, 1, -position.x, -position.y);
        p8g::scale(scale, scale);
        if(point) {
            p8g::point(point.value().x, point.value().y);
        }
        p8g::stroke(0, 0, 0, 120);
        grid->DrawGrid(position);

        p8g::stroke(255, 0, 0, 255);
        p8g::strokeWeight(20.0);
        p8g::point(robot_point.x, robot_point.y);

        p8g::stroke(0, 0, 0, 255);
        DrawLines(lines, Point2D{ 0, 0 });

        switch(draw_state) {
            case eDrawSate_Idle:
                break;
            case eDrawSate_Start:
                break;
            case eDrawState_Proccess:
                p8g::strokeWeight(LINE_THICKNESS);
                p8g::line(start_point.x, start_point.y, (mouseX + position.x) / scale, (mouseY + position.y) / scale);
                break;
        }
    };

    static void KeyPressed () {
        cout << "key = " << keyCode << endl;
        if(eCtrl_Key == keyCode) {
            is_ctrl_pressed = true;
        }
        if((eZ_Key == keyCode) && (true == is_ctrl_pressed)) {
            if(!lines.empty()) {
                lines.pop_back();
            }
        }
    };

    static void KeyReleased () {
        cout << "key = " << keyCode << endl;
        if(eCtrl_Key == keyCode) {
            is_ctrl_pressed = false;
        }
        if(eP_Key == keyCode) {
            for(auto n : lines) {
                cout << "(" << n.a.x << ", " << n.a.y << ")"
                     << " "
                     << "(" << n.b.x << ", " << n.b.y << ")" << endl;
            }
            parser->WriteLines(lines, robot_point, Point2D{ width, height });
        }

        if(eR_Key == keyCode) {
            auto lines = parser->ReadLines(window_width, window_height);
            for(auto n : lines) {
                cout << n.ToString() << endl;
            }
        }

        if(eRightArrow_Key == keyCode) {
            position.x = CheckBoundaries(position.x, -1);
            position.y = CheckBoundaries(position.y, 0);
        }
        if(eLeftArrow_Key == keyCode) {
            position.x = CheckBoundaries(position.x, 1);
            position.y = CheckBoundaries(position.y, 0);
        }
        if(eUpArrow_Key == keyCode) {
            position.x = CheckBoundaries(position.x, 0);
            position.y = CheckBoundaries(position.y, 1);
        }
        if(eDownArrow_Key == keyCode) {
            position.x = CheckBoundaries(position.x, 0);
            position.y = CheckBoundaries(position.y, -1);
        }
        if(ePlus_Key == keyCode) {
            UpdateScale(0.1);
        }
        if(eMinus_key == keyCode) {
            UpdateScale(-0.1);
        }
    };

    static void MouseReleased () {
        auto point = grid->FindPoint(mouseX, mouseY, threshold, position, scale);
        if((eLeft_Button == mouseButton) && (false == is_ctrl_pressed)) {
            switch(draw_state) {
                case eDrawSate_Idle:
                    draw_state = eDrawSate_Start;
                case eDrawSate_Start:
                    if(point) {
                        start_point = point.value();
                    } else {
                        start_point.x = (mouseX + position.x) / scale;
                        start_point.y = (mouseY + position.y) / scale;
                    }
                    draw_state = eDrawState_Proccess;
                    break;
                case eDrawState_Proccess:
                    if(point) {
                        end_point = point.value();
                    } else {
                        end_point.x = (mouseX + position.x) / scale;
                        end_point.y = (mouseY + position.y) / scale;
                    }
                    lines.push_back(Line2D{ start_point.x, start_point.y, end_point.x, end_point.y, LINE_THICKNESS });
                    draw_state = eDrawSate_Idle;
                    break;
            }
        } else if((eLeft_Button == mouseButton) && (true == is_ctrl_pressed)) {
            if(point) {
                robot_point = point.value();
            } else {
                robot_point.x = (mouseX + position.x) / scale;
                robot_point.y = (mouseY + position.y) / scale;
            }
        }

        if(eRight_Button == mouseButton) {
            is_right_button_pressed = false;
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
        if(eRight_Button == mouseButton) {
            mouse.x = mouseX;
            mouse.y = mouseY;
            is_right_button_pressed = true;
        }
    };
    static void MouseWheel (float delta) {
        if(true == is_ctrl_pressed) {
            UpdateScale(delta / 10);
        }
    };
};

Grid *Draw::grid;
Parser *Draw::parser;
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
uint32_t Draw::window_width;
uint32_t Draw::window_height;
Point2D Draw::robot_point;

int main () {
    Draw::Init(WINDOW_WIDTH * 2,
               WINDOW_HEIGHT * 2,
               WINDOW_WIDTH,
               WINDOW_HEIGHT,
               GRID_STEP,
               GRID_THRESHOLD,
               "outlines.txt");
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