#ifndef HEADER_H //to prevent already defined error during compiling
#define HEADER_H
#include <iostream>

//Author Aryaman Gupta
//writing signatures in header file for point2d.cpp
class Point2D{
    private: 
        int x, y;

    public:
        Point2D(); //default constructor declaration
        Point2D(int x, int y); //parameterized declaration

        //getter function for X & Y coords
        int getX() const; //const to make it read only
        int getY() const;

        //setter function for X & Y coord
        void setX(int x); //void type as it will return nothing
        void setY(int y);

        bool operator==(const Point2D& other) const; //operator == overloading for point2d objects

};

#endif