#ifndef HEADER_H //to prevent already defined error during compiling
#define HEADER_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

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


//Signatures for Maze2D
class Maze2D{
    private:
        vector<vector<int> > grid; //vector of int type vectors --> 2D grid
        int size; // N --> maze size NxN
    public:
        Maze2D(); //deafult constructor
        Maze2D(const string& filename); //to load maze from file
        bool loadfile(const string& filename); //reads and checks the loaded file, false if any discrepancies
        void display() const; //for printing grid in the cli
        int getSize() const; //returns N
        int getCell(int x, int y) const; // returns value of cell(0,1) whether it is accessible in path traversal or not
        bool isvalid_cell(int x, int y) const; //valid if cell in NxN matrix bounds and has value 1
};


#endif