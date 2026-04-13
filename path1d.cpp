#include "header.h" // to work with path1d class
#include <fstream> //for file handling
#include <stdexcept> //not necessary but i am using it to check for file opening errors

Path1D::Path1D() {} //initially path is empty 

Path1D::Path1D(const std::string &filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("cannot open file there is some error ");
	}

	for (int value; file >> value; ) {
		steps.push_back(value);
	}
	
	if (!isValidPath()) {
		throw std::runtime_error("invalid path data in file");
	}

}
bool Path1D::isValidPath() const {
	bool Zero_found = false; //to check if 0 is found in the path

	for (int step : steps) {
		if (step == 0) {
			Zero_found = true; //if 0 is found, set the flag to true
		} else if (step < 0 || step > 4) {
			return false; //invalid step value
		} else if (Zero_found) {
			return false; //if a non-zero step is found after a zero, it's invalid
		}
	}
	return true; //if all steps are valid
}
// now to display the path according to the step values


