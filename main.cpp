#include "header.h"
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 3) { //check if the correct number of command line arguments are provided
		std::cout << "Usage: " << argv << " <maze_file> <path_file>" << std::endl;
		return 1;
	}
	try {
		PathTraversal traversal(argv[1], argv[2]); //create a PathTraversal object with the provided maze and path files
		traversal.traverse(); //perform the path traversal
	}

		
	catch (const std::exception& e) { //catch any exceptions thrown during the traversal process
		std::cout << e.what() << std::endl; //print the error message from the exception
		return 1; //return a non-zero value to indicate an error occurred
	}
	return 0; //return 0 to indicate successful execution of the program
}
