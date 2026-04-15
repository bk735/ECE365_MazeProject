#include "header.h" //to work with path traversal class
#include <iostream>

PathTraversal::PathTraversal() {
	maze = nullptr; // no maze is loaded at beginning
	path = nullptr; //no path is loaded at beginning
	point = Point2D(0, 0); //starting point at (0,0)
}

PathTraversal::PathTraversal(const std::string& mazeFile, const std::string& PathFile) {
	maze = new Maze2D(mazeFile); //load the maze from the file
	path = new Path1D(PathFile); //load the path from the file
	point = Point2D(0, 0); //starting point at (0,0)

}

//destructor to free memory allocated for maze and path

PathTraversal::~PathTraversal() {
	delete maze; //free memory allocated for maze
	delete path; //free memory allocated for path
}


