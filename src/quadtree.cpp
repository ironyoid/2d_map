#include "quadtree.hpp"
#include <string>
#include <windows.h>
using std::cout;
using std::endl;
using std::string;

string point_to_str (Point2D point) {
    string ret = "(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
    return ret;
}

bool Point2D::operator==(const Point2D &other) const {
    return (x == other.x && y == other.y);
}

Point2D &Point2D::operator=(const Point2D &other) {
    x = other.x;
    y = other.y;
    return *this;
}

Point2D Point2D::operator/(const uint32_t other) {
    Point2D tmp;
    tmp.x = x / other;
    tmp.y = y / other;
    return tmp;
}

Point2D &Point2D::operator/=(const uint32_t other) {
    x /= other;
    y /= other;
    return *this;
}

bool Line2D::operator==(const Line2D &other) const {
    return (a == other.a && b == other.b);
}

QuadTree::QuadTree() {
    left_top = Point2D{ 0, 0 };
    right_bottom = Point2D{ 0, 0 };
};

QuadTree::QuadTree(Point2D left_top, Point2D size) {
    this->left_top = left_top;
    this->size = size;
    top_left_tree = nullptr;
    top_right_tree = nullptr;
    bottom_left_tree = nullptr;
    bottom_right_tree = nullptr;
}

void QuadTree::Split(void) {
    Point2D left_top1 = left_top;
    Point2D left_top2 = Point2D{ left_top.x + size.x / 2, left_top.y };
    Point2D left_top3 = Point2D{ left_top.x, left_top.y + size.y / 2 };
    Point2D left_top4 = Point2D{ left_top.x + size.x / 2, left_top.y + size.y / 2 };

    Point2D right_bottom1 = size / 2;
    Point2D right_bottom2 = size / 2;
    Point2D right_bottom3 = size / 2;
    Point2D right_bottom4 = size / 2;

    top_left_tree = new QuadTree(left_top1, right_bottom1);
    top_right_tree = new QuadTree(left_top2, right_bottom2);
    bottom_left_tree = new QuadTree(left_top3, right_bottom3);
    bottom_right_tree = new QuadTree(left_top4, right_bottom4);

    cout << point_to_str(left_top1) << " " << point_to_str(right_bottom1) << endl;
    cout << point_to_str(left_top2) << " " << point_to_str(right_bottom2) << endl;
    cout << point_to_str(left_top3) << " " << point_to_str(right_bottom3) << endl;
    cout << point_to_str(left_top4) << " " << point_to_str(right_bottom4) << endl;
    cout << endl;

    /*     top_left_tree = new QuadTree(left_top, size / 2);
    top_right_tree = new QuadTree(Point2D{ left_top.x + size / 2, left_top.y }, size / 2);
    bottom_left_tree = new QuadTree(Point2D{ left_top.x, left_top.y + size / 2 }, size / 2);
    bottom_right_tree = new QuadTree(Point2D{ left_top.x + size / 2, left_top.y + size / 2 }, size / 2); */

    /*     Point2D left_top1 = left_top;
    Point2D left_top2 = Point2D{ right_bottom.x / 2, left_top.y };
    Point2D left_top3 = Point2D{ left_top.x, right_bottom.y / 2 };
    Point2D left_top4 = Point2D{ right_bottom.x / 2, right_bottom.y / 2 };

    Point2D right_bottom1 = right_bottom / 2;
    Point2D right_bottom2 = Point2D{ right_bottom.x, right_bottom.y / 2 };
    Point2D right_bottom3 = Point2D{ right_bottom.x / 2, right_bottom.y };
    Point2D right_bottom4 = Point2D{ right_bottom.x, right_bottom.y };

    cout << point_to_str(left_top1) << " " << point_to_str(right_bottom1) << endl;
    cout << point_to_str(left_top2) << " " << point_to_str(right_bottom2) << endl;
    cout << point_to_str(left_top3) << " " << point_to_str(right_bottom3) << endl;
    cout << point_to_str(left_top4) << " " << point_to_str(right_bottom4) << endl;
    cout << endl;
    top_left_tree = new QuadTree(left_top1, right_bottom1);
    top_right_tree = new QuadTree(left_top2, right_bottom2);
    bottom_left_tree = new QuadTree(left_top3, right_bottom3);
    bottom_right_tree = new QuadTree(left_top4, right_bottom4); */
}

uint32_t QuadTree::GridSize(void) {
    cout << "Grid size: " << size.x << endl;
    return (size.x);
}

void CreateQuadTree (QuadTree *root, uint32_t grid_size) {
    /* cout << "left_top = (" << root->left_top.x << ", " << root->left_top.y << ") "
         << "right_bottom = (" << root->right_bottom.x << ", " << root->right_bottom.y << ")" << endl; */
    if(root->GridSize() <= grid_size) {
        return;
    }
    root->Split();
    Sleep(1000);
    CreateQuadTree(root->top_left_tree, grid_size);
    CreateQuadTree(root->top_right_tree, grid_size);
    CreateQuadTree(root->bottom_left_tree, grid_size);
    CreateQuadTree(root->bottom_right_tree, grid_size);
}
