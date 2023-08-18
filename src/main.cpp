#include "p8g.hpp"
#include "quadtree.hpp"

using namespace p8g;
using std::cout;
using std::endl;

void p8g::draw() {
    background(250);
    strokeWeight(10.0);
    line(100, 100, 300, 300);
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
    Point2D x{ 0, 0 };
    Point2D y{ 100, 100 };
    QuadTree root(x, y);
    /*     cout << root.left_top.x << " " << root.left_top.y << endl;
    cout << root.right_bottom.x << " " << root.right_bottom.y << endl; */
    CreateQuadTree(&root, 25);
}