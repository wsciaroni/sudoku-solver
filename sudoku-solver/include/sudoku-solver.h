// sudoku-solver.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <array>
#include <vector>

#include "Cell.h"

/** @brief Solution to Sudoku problems
 * Provide a public interface to solveSudoku problems efficiently
 */
class Solution
{
public:
	/// @brief Hold the number of rows or cols in a standard Sudoku board
	static const size_t SUDOKU_SIZE = 9;

private:
	/// @brief True if Logging is enabled throughout the application
	static const bool loggingEnabled = false;

	template <typename T = uint8_t>
	char intToChar(T i) {
		return i+'0';
	};

	template <typename T = uint8_t>
	T charToInt(char c) {
		return c-'0';
	};

	/**
	 * @brief Print the value in each of the board's cells
	 *
	 * @param vect The board to print
	 */
	void inline printVectorState(std::array<std::array<Cell, SUDOKU_SIZE>, SUDOKU_SIZE>& vect);

	/**
	 * @brief Initialize the Board
	 *
	 * Allocate the 9x9 area
	 */
	void inline initialize();

	/**
	 * @brief Set the Value of a cell
	 *
	 * This function sets the value of a cell and calls updateConstraints if required
	 *
	 * @param i The x coordinate
	 * @param j The y coordinate
	 * @param value The value to set in the cell
	 * @return true If the value was logically sound
	 * @return false If the value or following deductions were inconsistent.
	 */
	bool inline setValue(int i, int j, int value);

	/**
	 * @brief Update the Constraints on a cell
	 *
	 * This functions stores at coordinate [i,j] that we can not have `excludedValue` in the future.
	 *
	 * This calls setValue as needed to follow the logical dependencies
	 *
	 * @param i The x coordinate
	 * @param j The y coordinate
	 * @param excludedValue The value that can no longer be set at this coordinate
	 * @return true If the value could logically be excluded
	 * @return false If this value or following deductions were inconsistent
	 */
	bool inline updateConstraints(int i, int j, int excludedValue);

	/// @brief Keep a list of empty cells at the beginning to back track
	std::vector<std::pair<int, int>> bt;

	/**
	 * @brief Sort the remaining empty cells
	 *
	 * This function sorts the bt array based on the number of remaining non-excluded values at each cell
	 *
	 * @param it The iterator to start sorting with
	 *
	 * Sorts from it through bt.end
	 */
	void inline sortBt(const std::vector<std::pair<int, int>>::iterator &it);

	/**
	 * @brief Populate the bt array with coordinates of empty cells
	 *
	 * @return The value of backtrack once the bt array is populated
	 */
	bool inline findValuesForEmptyCells();

	/**
	 * @brief Perform the Backtrack algorithm on the Sudoku array
	 *
	 * @param k The iterator to start at
	 * @return true If the value can be set to any of its remaining possibilities based on the current state
	 * @return false If the value cannot be set to a valid value based on the current state
	 */
	bool inline backtrack(std::vector<std::pair<int, int>>::iterator k);

	/// @brief Hold the current state of the board
	std::array<std::array<Cell, SUDOKU_SIZE>, SUDOKU_SIZE> cells; // 9x9 vector of cell

public:
	/**
	 * @brief Solve the Sudoku puzzle
	 *
	 * @param board The sudoku puzzle to solve
	 * 
	 * If the sudoku can't be solve, the board remains untouched
	 */
	void solveSudoku(std::array<std::array<char, Solution::SUDOKU_SIZE>, Solution::SUDOKU_SIZE>&board);
};
