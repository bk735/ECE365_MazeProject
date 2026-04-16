#include "header.h" //to work with path traversal class
#include <iostream>
#include <vector>
#include <cstddef>
#include <iterator>

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

bool PathTraversal::traverse() {
	if (maze == nullptr || path == nullptr) { //check if maze and path are loaded
		std::cout << "Error: " << (maze == nullptr && path == nullptr ? "Maze and Path" : (maze == nullptr ? "Maze" : "Path")) << " not loaded!" << std::endl;//print specific error message for maze, path or both not loaded
		return false; //stop traversal if either is not loaded
	}
	
	if (!(maze->isValidMaze()) || !(path->isValidPath())) { //check if maze or path or both are valid
		std::cout << "Error: Invalid " << (!(maze->isValidMaze()) && !(path->isValidPath()) ? "Maze and Path" : (!(maze->isValidMaze()) ? "Maze" : "Path")) << std::endl;
		return false; //stop traversal if maze or path or both are invalid
	}

	path_points.clear(); //clear any previous path points
	point.setX(0); 
	point.setY(0); //reset starting point to (0,0)

	if (!(maze->isValidCell(point.getX(), point.getY()))) { //check if starting point is valid
		std::cout << "Error: Starting point (0,0) is not accessible (must be 1)." << std::endl;
		return false; //stop traversal if starting point is not valid
	}

	path_points.push_back(point); //add starting point to path points

	for (int i = 0; i < path->getNumSteps(); i++) { //iterate through each step in the path
		int step = path->getStep(i); //get the current step

		int currX = point.getX();
		int currY = point.getY();

		switch (step) { //update point coordinates based on the step direction
			case 1: // Up
				currX -= 1;
				break;
			case 2: // Right
				currY += 1;
				break;
			case 3: // Down
				currX += 1;
				break;
			case 4: // Left
				currY -= 1;
				break;
			case 0: // End of path
				std::cout << "Successfully reached the end of the path. Marker at: " << i << std::endl;
				return true; //successfully reached end of path
			default:
				std::cout << "Error: Invalid step value " << step << " at index " << i << ". Only values [0,1,2,3,4] are allowed." << std::endl;
				return false; //stop traversal if invalid step value is found
		}

		if (!maze->isValidCell(currX, currY)) { //check if the new point is valid after the move
			std::cout << "Error: Step " << i << " leads to an invalid cell (" << currX << ", " << currY << ")" << std::endl;
			return false; //stop traversal if an invalid cell is reached
		}

		point.setX(currX); //update point's X coordinate
		point.setY(currY); //update point's Y coordinate
		path_points.push_back(point); //add the new valid point to the path points
	}
	return true; //successfully traversed the entire path without errors
}

void PathTraversal::displayResult() const {
	if (path_points.empty()) {
		std::cout << "No path points to display." << std::endl;
		return;
	}

	std::cout << "Path Traversed:";
	int stepNum = 0;
	for (const auto& p : path_points) {
		std::cout << "Step " << stepNum << ": (" << p.getX() << ", " << p.getY() << ")" << std::endl;
		stepNum++;
	}
}

//destructor to free memory allocated for maze and path
PathTraversal::~PathTraversal() {
	delete maze; //free memory allocated for maze
	delete path; //free memory allocated for path
}


