#ifndef HEADER_H //to prevent already defined error during compiling
#define HEADER_H
#include <iostream>
#include <vector>
#include <string>



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
        bool operator==(const Point2D &other) const; //operator == overloading for point2d objects
};


//Signatures for Maze2D
class Maze2D{
    private:
        std::vector<std::vector<int> > grid; //vector of int type vectors --> 2D grid
        int size; // N --> maze size NxN
    public:
        Maze2D(); //default constructor
        Maze2D(const std::string &filename); //to load maze from file
        bool isValidMaze() const; //reads and checks the loaded file, false if any discrepancies
        void displayMaze() const;//for printing 
		void saveMaze(const std::string &filename) const; //to save the maze to a file
        int getSize() const; //returns N
        int getCell(int x, int y) const; // returns value of cell(0,1) whether it is accessible in path traversal or not
        bool isValidCell(int x, int y) const; //valid if cell in NxN matrix bounds and has value 1
};

//Signatures for Path1D
class Path1D{
    private:
        std::vector<int> steps; // 1=Up, 2=Right, 3=Down, 4=Left, 0=end
        
    public:
        Path1D(); //default constructor
        Path1D(const std::string &filename); //to load path file
        bool isValidPath() const; //to check for any discrepancies: only [0,1,2,3,4] steps are allowed AND 0 should only be followed by zeros
        void displayPath() const; //printing number-->direction of the step (eg: 1-->Up)
		void savePath(const std::string &filename) const; //to save the path to a file
        int getNumSteps() const; //total entries in path list
        int getStep(int index) const; //eg: get_step(0) returns say 1(up)ie. the first value in the loaded path, then get_step(1) for the second value and so on. 

};

//Signatures for PathTraversal
class PathTraversal{
    private:
        Maze2D* maze; //instance of Maze2D
        Path1D* path; //instance of Path1D
        Point2D point; //instance of Point2D

		std::vector<Point2D> path_points; //to store the points traversed in the path
    public:
        PathTraversal();
        PathTraversal(const std::string &mazeFile, const std::string &pathFile); //loads both maze and path file
        bool traverse(); /* run valid_maze() → if false, print error
                             run valid_path() → if false, print error, stop
                             walk step by step using point, checking as you go */
        void displayResult() const; //prints final success/error message
		~PathTraversal(); //destructor to free memory allocated for maze and path

};
#endif