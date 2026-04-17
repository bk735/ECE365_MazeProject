#include "header.h" // to work with path1d class
#include <fstream> //for file handling
#include <stdexcept> //not necessary but i am using it to check for file opening errors
#include <sstream> //for string stream to read values from file

Path1D::Path1D() {} //initially path is empty 

Path1D::Path1D(const std::string &filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("-E-: Error reading path file '" + filename + "'.");
	}

	std::string line;
	bool path_read = false; //flag to check if any path data is read from the file

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::vector<int> temp;
		int value;

		while(ss >> value) {
			temp.push_back(value); //store the values in a temporary vector
		}
		if (!temp.empty()) {
			if (path_read) {
				throw std::runtime_error("-E-: Path has already been read. Path file can't have multiple paths or non-comment rows.");
			}
			steps = temp; //assign the temporary vector to the steps vector
			path_read = true; //set the flag to true after reading the path
		}
	}
	if (steps.empty()) {
		throw std::runtime_error("-E-: Error reading path file '" + filename + "'.");
	}
	isValidPath(); //validate the path after reading it from the file

	

}
bool Path1D::isValidPath() const {
	bool Zero_found = false; //to check if 0 is found in the path

	for (int step : steps) {
		if (step == 0) {
			Zero_found = true; //if 0 is found, set the flag to true
		} else if (step < 0 || step > 4) {
			throw std::runtime_error("-E-: Invalid path entry '" + std::to_string(step) + "'.");//invalid step value
		} else if (Zero_found) {
			throw std::runtime_error("-E-: Invalid path. Path can't have a non-zero entry after a string of zeroes.");//if a non-zero step is found after a zero, it's invalid
		}
	}
	return true; //if all steps are valid
}
// now to display the path according to the step values

void Path1D::displayPath() const {
	std::vector<std::string> directions = { "End", "Up", "Right", "Down", "Left" };

	for (int step : steps) {
		if (step >= 0 && step <= 4) {
			std::cout << directions[step] << " "; //print the corresponding direction for each step]
		}
	}

	std::cout << std::endl; 
}

void Path1D::savePath(const std::string& filename) const {
	std::ofstream file(filename);
	if (!file) {
		throw std::runtime_error("-E-: Error writing path file '" + filename + "'.");
	}

	for (int step : steps) {
		file << step <<" "; //write each step to the file on a new line
	}
	file.close(); //close the file after writing

}

int Path1D::getNumSteps() const {
	return steps.size(); // to return total number of steps
}

int Path1D::getStep(int index) const {
	if (index < 0 || index >= steps.size()) {
		throw std::out_of_range("index out of range"); //check for valid index
	}
	return steps[index]; //to return steps at the given index
}

