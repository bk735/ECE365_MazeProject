#include "header.h" 
#include <fstream> 
#include <stdexcept> 
#include <sstream>
#include <vector>

Maze2D::Maze2D(): size(0) {}

Maze2D::Maze2D(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("-E-: Error reading maze file '" + filename + "'.");
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
		throw std::runtime_error("-E-: Error reading maze file '" + filename + "'.");
	}

	if (grid[0][0] != 1) {
		throw std::runtime_error("-E-: The top left entry of the maze MUST be 1.");
	}
	isValidMaze();
	// The validation check belongs HERE in the constructor!
	
}

bool Maze2D::isValidMaze() const {
	if (grid.empty()) {
		return false;
	}

	int n = grid.size();

	for (int r = 0; r < n; ++r) {
		// Check if the row length matches the maze height
		if (grid[r].size() != grid[0].size()) {
			throw std::runtime_error("-E-: All rows of the maze MUST have the same length.");
		}

		// Check every cell in the row for valid numbers
		for (int c = 0; c < grid[r].size(); ++c) {
			int cellValue = grid[r][c];

			if (cellValue != 0 && cellValue != 1) {
				throw std::runtime_error("-E-: Invalid maze entry '" + std::to_string(cellValue) + "'.");
			}
		}
	} // End of the row loop
	if (grid.size() != grid[0].size()) {
		throw std::runtime_error("-E-: #rows MUST be equal to #cols.");
	}

	if (grid[0][0] != 1) {
		throw std::runtime_error("-E-: The top left entry of the maze MUST be 1.");
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
		throw std::runtime_error("-E-: Error writing maze file '" + filename + "'.");
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