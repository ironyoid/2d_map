#include "p8g.hpp"

using namespace p8g;

void p8g::draw() {
    background(gray);
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
    run(320, 320, "Hello rectangle!");
}