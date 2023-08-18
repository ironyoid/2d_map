#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"
#include "grid.hpp"

using namespace p8g;
using std::cout;
using std::endl;
using std::vector;

#define WINDOW_WIDTH  (1000U)
#define WINDOW_HEIGHT (1000U)
Grid *grid;

void p8g::draw() {
    background(250);
    grid->DrawGrid();
    auto point = grid->FindPoint(mouseX, mouseY);
    p8g::strokeWeight(10.0);
    p8g::stroke(0, 255, 0, 200);
    p8g::point(point.x, point.y);
}

void p8g::keyPressed() {
}
void p8g::keyReleased() {
}
void p8g::mouseMoved() {
}
void p8g::mousePressed() {
}
void p8g::mouseReleased() {
}
void p8g::mouseWheel(float delta) {
}

int main () {
    grid = new Grid(50, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0);
    run(WINDOW_WIDTH, WINDOW_HEIGHT, "2d_engine");
}