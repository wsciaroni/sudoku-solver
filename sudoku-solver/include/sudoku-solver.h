// sudoku-solver.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vector>

#include "Cell.h"

class Solution {
	static const bool loggingEnabled = false;

	void inline printVectorState(std::vector<std::vector<Cell>>& vect);

	void inline initialize();

	bool inline setValue(int i, int j, int value);

	bool inline updateConstraints(int i, int j, int excludedValue);

	// Keep a list of empty cells at the beginning to back track
	std::vector<std::pair<int, int>> bt;

	void inline sortBt(const std::vector<std::pair<int, int>>::iterator& it);

	bool inline findValuesForEmptyCells();

	bool inline backtrack(std::vector<std::pair<int, int>>::iterator k);

	std::vector<std::vector<Cell>> cells; // 9x9 vector of cell

public:
	void solveSudoku(std::vector<std::vector<char>>& board);
};
