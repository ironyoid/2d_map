#include <vector>
#include "p8g.hpp"
#include "quadtree.hpp"

using namespace p8g;
using std::cout;
using std::endl;
using std::vector;

struct Quad {
    Point2D left_top;
    Point2D size;
};

vector<Quad> global_vector;

void add_quad_to_list (vector<Quad> &list, QuadTree *node) {
    if(node != nullptr) {
        Quad ret;
        ret.left_top = node->left_top;
        ret.size = node->size;
        list.push_back(ret);
    }
}

vector<Quad> draw_tree (QuadTree *root) {
    static vector<Quad> ret;
    if(root == nullptr) {
        return ret;
    }
    add_quad_to_list(ret, root->top_left_tree);
    add_quad_to_list(ret, root->top_right_tree);
    add_quad_to_list(ret, root->bottom_left_tree);
    add_quad_to_list(ret, root->bottom_right_tree);

    /*     p8g::rect(root->top_left_tree->left_top.x,
              root->top_left_tree->left_top.y,
              root->top_left_tree->size.x,
              root->top_left_tree->size.y);
    p8g::rect(root->top_right_tree->left_top.x,
              root->top_right_tree->left_top.y,
              root->top_right_tree->size.x,
              root->top_right_tree->size.y);
    p8g::rect(root->bottom_left_tree->left_top.x,
              root->bottom_left_tree->left_top.y,
              root->bottom_left_tree->size.x,
              root->bottom_left_tree->size.y);
    p8g::rect(root->bottom_right_tree->left_top.x,
              root->bottom_right_tree->left_top.y,
              root->bottom_right_tree->size.x,
              root->bottom_right_tree->size.y); */

    draw_tree(root->top_left_tree);
    draw_tree(root->top_right_tree);
    draw_tree(root->bottom_left_tree);
    draw_tree(root->bottom_right_tree);
    return ret;
}

void p8g::draw() {
    background(250);
    for(auto n : global_vector) {
        p8g::rect(n.left_top.x, n.left_top.y, n.size.x, n.size.y);
    }
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
    Point2D y{ 500, 500 };
    QuadTree global_tree(x, y);
    CreateQuadTree(&global_tree, 125);
    global_vector = draw_tree(&global_tree);
    /*     for(auto n : vector_tree) {
        cout << "(" << n.left_top.x << ", " << n.left_top.y << ")"
             << " (" << n.size.x << ", " << n.size.y << ")" << endl;
    } */
    run(500, 500, "2d_engine");
}