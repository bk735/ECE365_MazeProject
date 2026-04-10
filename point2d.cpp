#include "header.h" //to work with point2d class

//FUNCTION DEFINITONS
//default constructor
Point2D::Point2D() {
    x = 0;
    y = 0;
}

//parameterised constructor
Point2D::Point2D(int x_coord, int y_coord) {
    x = x_coord;
    y = y_coord;
}

//getter functions
int Point2D::getX() const {
    return x;
}

int Point2D::getY() const {
    return y;
}

//setter functions
void Point2D::setX(int x_coord) {
    x = x_coord;
}

void Point2D::setY(int y_coord) {
    y = y_coord;
}

//operator overloading
bool Point2D::operator==(const Point2D& other) const {
    return (x == other.x && y == other.y);
}