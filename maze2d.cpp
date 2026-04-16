#include "header.h" 
#include <fstream> 
#include <stdexcept> 
#include <sstream>
#include <vector>

Maze2D::Maze2D(): size(0) {}

Maze2D::Maze2D(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Cant open maze file: " + filename);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);

		int value;

		while (ss >> value) {
			row.push_back(value);
		}

		if (!row.empty()) {
			grid.push_back(row);
		}
	}

	

	size = grid.size();

	if (size == 0) {
		throw std::runtime_error("error: maze file is empty");
	}

	if (grid[0][0] != 1) {
		throw std::runtime_error("error: the starting point of the maze must be 1");
	}

	// The validation check belongs HERE in the constructor!
	if (!isValidMaze()) {
		throw std::runtime_error("Error: Invalid maze data (not square or contains invalid numbers).");
	}
}

bool Maze2D::isValidMaze() const {
	if (grid.empty()) {
		return false;
	}

	int n = grid.size();

	for (int r = 0; r < n; ++r) {
		// Check if the row length matches the maze height
		if (grid[r].size() != n) {
			std::cout << "Error: maze is not a square(N x N). " << std::endl;
			return false;
		}

		// Check every cell in the row for valid numbers
		for (int c = 0; c < n; ++c) {
			int cellValue = grid[r][c];

			if (cellValue != 0 && cellValue != 1) {
				std::cout << "error: Invalid character found at (" << r << ", " << c << ").Only 0 and 1 are allowed." << std::endl;
				return false;
			}
		}
	} // End of the row loop

	if (grid[0][0] != 1) {
		std::cout << "Error: The top-left starting cell must be 1." << std::endl;
		return false;
	}

	// Only return true after checking EVERYTHING
	return true;
}

void Maze2D::displayMaze() const {
	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			std::cout << grid[r][c] << " ";
		}
		std::cout << std::endl;
	}
}

void Maze2D::saveMaze(const std::string& filename) const {
	std::ofstream file(filename);

	if (!file) {
		throw std::runtime_error("error: cannot open file to save maze.");
	}

	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			file << grid[r][c] << " ";
		}
		file << std::endl;
	}
}

int Maze2D::getSize() const {
	return size;
}

int Maze2D::getCell(int x, int y) const {
	return grid[x][y];
}

bool Maze2D::isValidCell(int x, int y) const {
	if (x < 0 || x >= size || y < 0 || y >= size) {
		return false;
	}

	if (grid[x][y] == 1) {
		return true;
	}

	return false;
}