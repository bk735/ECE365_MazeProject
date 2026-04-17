#include "header.h"
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 3) { //check if the correct number of command line arguments are provided
		std::cout << "Usage: " << argv[0] << " <maze_file> <path_file>" << std::endl;
		return 1;
	}
	try {
		PathTraversal traversal(argv[1], argv[2]); //create a PathTraversal object with the provided maze and path files

		bool result = traversal.traverse(); //perform the path traversal and store the result (success or failure)
		if (result) {
			std::cout << "Traversal successful" << std::endl;
		}
		else {
			std::cout << "Traversal failed" << std::endl;
		}
		traversal.displayResult(); //display the result of the traversal, including any error messages or success messages
	}
	catch (const std::exception& e) { //catch any exceptions thrown during the traversal process
		std::cout << "An error occurred: " << e.what() << std::endl; //print the error message from the exception
		return 1; //return a non-zero value to indicate an error occurred
	}
	return 0; //return 0 to indicate successful execution of the program
}
