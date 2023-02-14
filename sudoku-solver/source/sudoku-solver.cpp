#include "sudoku-solver.h"

#include <iostream>
#include <cassert>
#include <algorithm>

inline void Solution::printVectorState(std::array<std::array<Cell,Solution::SUDOKU_SIZE>, Solution::SUDOKU_SIZE>& vect) {
	if (!loggingEnabled) return;
	std::cout << "[" << std::endl;
	for (int i = 0; i < SUDOKU_SIZE; i++) {
		std::cout << "[";
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			std::cout << "\"" << intToChar(vect[i][j].getValue()) << "\"";
		}
		std::cout << "]," << std::endl;
	}
	std::cout << "]" << std::endl;
}

inline void Solution::initialize() {
	if (loggingEnabled) {
		std::cout << "Initialzied all cells" << std::endl;
	}
}

inline bool Solution::setValue(int i, int j, int value) {
	if (loggingEnabled) {
		std::cout << "Setting value at: [" << i << "," << j << "]: " << intToChar(value) << std::endl;
	}
	Cell& c = cells[i][j];

	// We've already determined this value and it matches
	if (c.valueIsSet() && c.getValue() == value) {
		if (loggingEnabled) {
			std::cout << "Value already set" << std::endl;
		}
		return true;
	}

	// If we've already deterimined that this cell can't be this value, return false
	if (c.checkIfValueCouldNotBe(value)) {
		if (loggingEnabled) {
			std::cout << "Cannot set, this violates the constraints from earlier..." << std::endl;
		}
		return false;
	}

	if (loggingEnabled) {
		std::cout << "Setting this value." << std::endl;
	}

	c.setCellValue(value);

	for (int k = 0; k < SUDOKU_SIZE; k++) {
		// Apply constraints to the row
		if (i != k) {
			if (!updateConstraints(k, j, value)) {
				if (loggingEnabled) {
					std::cout << "Unable to apply the constraints on the row" << std::endl;
				}
				return false; // Unable to update the constraints on the row
			}
		}

		// Apply constraints to the column
		if (j != k) {
			if (!updateConstraints(i, k, value)) {
				if (loggingEnabled) {
					std::cout << "Unable to apply the constraints on the column" << std::endl;
				}
				return false; // Unable to update the constraints on the column
			}
		}

		// To the 3x3 square
		// Index of corners of the square.
		int ix = (i / 3) * 3 + k / 3;
		int jx = (j / 3) * 3 + k % 3;
		if (ix != i && jx != j) {
			if (!updateConstraints(ix, jx, value)) {
				if (loggingEnabled) {
					std::cout << "Unable to apply the constraints on the square" << std::endl;
				}
				return false; // Unable to update the constraints on the 3x3 square.
			}
		}
	}

	return true;
}

inline bool Solution::updateConstraints(int i, int j, int excludedValue) {
	if (loggingEnabled) {
		std::cout << "Attempting to exclude the value " << intToChar(excludedValue) << " at [" << i << "," << j << "]" << std::endl;
	}
	Cell& c = cells[i][j];

	if (c.checkIfValueCouldNotBe(excludedValue)) {
		if (loggingEnabled) {
			std::cout << "Constraints already set" << std::endl;
		}
		return true;
	}
	if (c.valueIsSet() && c.getValue() == excludedValue) {
		if (loggingEnabled) {
			std::cout << "Can't constrain field. Value already set" << std::endl;
		}
		return false; // We were wrong in our attempt
	}

	// If the value could be valid, AND the constraints don't have this excluded, let's remove it from the constraints
	c.excludeValue(excludedValue);

	if (c.getNumberOfRemainingPossibilities() > 1) return true; // If we haven't reached the last number of possibilities

	
	return setValue(i,j,c.getRemainingPossibility());

	// This should never happen
	// throw std::logic_error("Somehow the Cell has 1 possibility remaining, but none available in the set function");
	return false;
}

inline void Solution::sortBt(const std::vector<std::pair<int, int>>::iterator& it) {
	// Sort the list by the number of possibilites remaining in each cell
	std::sort(it, bt.end(), [this](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return cells[a.first][a.second].getNumberOfRemainingPossibilities() < cells[b.first][b.second].getNumberOfRemainingPossibilities();
		});
}

inline bool Solution::findValuesForEmptyCells() {
	bt.clear();

	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			if (!cells[i][j].valueIsSet()) {
				bt.emplace_back(i, j);
			}
		}
	}

	// Sort the list by the number of possibilites remaining in each cell
	sortBt(bt.begin());
	return backtrack(bt.begin());
}

inline bool Solution::backtrack(std::vector<std::pair<int, int>>::iterator k) {
	if (k == bt.end()) return true;

	auto i = (*k).first;
	auto j = (*k).second;

	// Fast path
	if (cells[i][j].valueIsSet()) {
		if (loggingEnabled) {
			std::cout << "BSorting: " << std::distance(k + 1, bt.end()) << " elements" << std::endl;
		}
		//sortBt(k + 1);
		return backtrack(k + 1);
	}

	auto possibilities = cells[i][j].getRemainingPossiblities();

	auto snapshot = cells; // Create a copy of the array as a backup

	for(auto v : possibilities) {
		if (setValue(i, j, v)) {
			if (loggingEnabled) {
				std::cout << "ASorting: " << std::distance(k + 1, bt.end()) << " elements" << std::endl;
			}
			sortBt(k + 1);
			if (backtrack(k + 1)) {
				return true;
			}
		}
		cells = snapshot;
	}
	return false;
}

void Solution::solveSudoku(std::array<std::array<char, Solution::SUDOKU_SIZE>, Solution::SUDOKU_SIZE>& board) {
	initialize();

	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			if (board[i][j] != '.') {
				if (!setValue(i, j, charToInt(board[i][j])))
				{
					if (loggingEnabled) {
						std::cout << "Unable to initialize, Either invalid, or unsolvable" << std::endl;
					}
					return; // unsolvable. Can't set the values that we were given
				}
			}
		}
	}

	if (!findValuesForEmptyCells()) return; // unsolvable.

	for (int i = 0; i < SUDOKU_SIZE; i++) {
		for (int j = 0; j < SUDOKU_SIZE; j++) {
			if (cells[i][j].valueIsSet()) {
				board[i][j] = intToChar(cells[i][j].getValue());
			}
		}
	}

	printVectorState(cells);
}
