#include "header.h" //to work with path traversal class
#include <iostream>
#include <vector>

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
	maze->displayMaze(); //display the loaded maze
	std::cout << std::endl; //add a line break for better readability
	path->displayPath(); //display the loaded path
	std::cout << std::endl; //add a line break for better readability

	

	path_points.clear(); //clear any previous path points
	point.setX(0);
	point.setY(0); //reset starting point to (0,0)

	if (!(maze->isValidCell(point.getX(), point.getY()))) { //check if starting point is valid
		std::cout << "-E-: The top left entry of the maze MUST be 1." << std::endl;
		return false; //stop traversal if starting point is not valid
	}

	path_points.push_back(point); //add starting point to path points

	int steps_taken = 0; //to keep track of the number of steps taken

	for (int i = 0; i < path->getNumSteps(); i++) { //iterate through each step in the path
		int step = path->getStep(i); //get the current step
		if (step == 0) {
			break; //if end of path is reached, stop iterating through steps
		}

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
		
		default:
			return false; //stop traversal if invalid step value is found
		}


		if (currX < 0) {
			std::cout << "-E-: Invalid path, taking it beyond the top edge of the maze after "
				<< steps_taken << " steps." << std::endl;
			return false;
		}
		if (currX >= maze->getSize()) {
			std::cout << "-E-: Invalid path, taking it beyond the bottom edge of the maze after "
				<< steps_taken << " steps." << std::endl;
			return false;
		}
		if (currY < 0) {
			std::cout << "-E-: Invalid path, taking it beyond the left edge of the maze after "
				<< steps_taken << " steps." << std::endl;
			return false;
		}
		if (currY >= maze->getSize()) {
			std::cout << "-E-: Invalid path, taking it beyond the right edge of the maze after "
				<< steps_taken << " steps." << std::endl;
			return false;
		}

		if (!maze->isValidCell(currX, currY)) { //check if the new point is valid after the move
			std::cout << "-E-: Invalid path, visits an illegal cell ("
				<< currY << ", " << currX
				<< ") of the maze (origin being at top-left corner)." << std::endl;
			return false; //stop traversal if an invalid cell is reached
		}

		Point2D newPoint(currX, currY); //create a new point with the updated coordinates

		for (const auto& p : path_points) //check if new point has already been visited
		{
			if (p == newPoint) {
				std::cout << "-E-: Invalid path, revisits a traversed path at coordinates ("
					<< currY << ", " << currX
					<< ") (origin being at top-left corner)." << std::endl;
				return false;
			}
		}

		point = newPoint; //update current point to the new point
		path_points.push_back(point); //add the new point to the path points
		steps_taken++; //increment the steps taken
		if (point.getX() == maze->getSize() - 1 && point.getY() == maze->getSize() - 1) {
			if (i != path->getNumSteps() - 1 && path->getStep(i + 1) != 0) {
				std::cout << "-I-: Invalid path. Reached end of maze after "
					<< steps_taken
					<< " steps, but path not complete yet!" << std::endl;
				return false;
			}
		}
	}
	

	if (point.getX() == maze->getSize() - 1 && point.getY() == maze->getSize() - 1) { //check if the final point is the exit (N-1, N-1)
		std::cout << "-I-: Path traversal completed successfully in "
			<< steps_taken << " steps." << std::endl;
		return true; //traversal successful
	}
	else {
		std::cout << "-I-: Invalid path. Reached end of path after "
			<< steps_taken
			<< " steps, but not reached the end of the maze yet!" << std::endl;
		return false; //traversal completed but did not reach exit
	}

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


