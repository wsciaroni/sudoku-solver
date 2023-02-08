
#include "sudoku-solver.h"
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <chrono>

/**
 * @brief Read the input string to get the input vector
 * @param filename 
 * @return 
 * 
 * SAMPLE input:
 * [["5","3",".",".","7",".",".",".","."],
 *  ["6",".",".","1","9","5",".",".","."],
 *  [".","9","8",".",".",".",".","6","."],
 *  ["8",".",".",".","6",".",".",".","3"],
 *  ["4",".",".","8",".","3",".",".","1"],
 *  ["7",".",".",".","2",".",".",".","6"],
 *  [".","6",".",".",".",".","2","8","."],
 *  [".",".",".","4","1","9",".",".","5"],
 *  [".",".",".",".","8",".",".","7","9"]]
*/
std::array<std::array<char, 9>, 9> readFileToArr(const std::string& filename) {
	std::ifstream source;
	source.open(filename);

	std::array<std::array<char,9>,9> board;
	char c = '#';
	source >> std::skipws >> c; // Read "["
	for (int i = 0; i < 9; i++) {
		source >> std::skipws >> c; // Read "["
		for (int j = 0; j < 9; j++) {
			source >> std::skipws >> c; // Read "\""
			source >> std::skipws >> c; // Read "Character"
			board[i][j] = c;
			//std::cout << "Character " << c << std::endl;
			source >> std::skipws >> c; // Read "\""
			source >> std::skipws >> c; // Read "," and line ending "]"
		}
		source >> std::skipws >> c; // Read "," and last "]
	}
	source.close();
	return board;
}

void printArr(const std::array<std::array<char, 9>, 9>& arr) {
	int colCount = 0;
	for (const auto& v : arr) {
		int rowCount = 0;
		colCount++;
		for (const auto& c : v) {
			std::cout << " " << c;
			rowCount++;
			if (rowCount % 3 == 0) {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
		if (colCount % 3 == 0) {
			std::cout << std::endl;
		}
	}
}

int main(int argc, char** argv)
{
	if (argc < 2) { return -1; }
	std::string inputFilename(argv[1]);
	std::array<std::array<char, 9>, 9> board = readFileToArr(inputFilename);

	std::cout << "Array read in as follows: " << std::endl << std::endl;
	printArr(board);

	std::cout << std::endl << "Solving ..." << std::endl << std::endl;
	Solution s;
	auto startTime = std::chrono::high_resolution_clock::now();
	s.solveSudoku(board);
	auto stopTime = std::chrono::high_resolution_clock::now();

	// Subtract stop and start timepoints and
	// cast it to required unit. Predefined units
	// are nanoseconds, microseconds, milliseconds,
	// seconds, minutes, hours. Use duration_cast()
	// function.
	auto durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
	auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime);

	// To get the value of duration use the count()
	// member function on the duration object
	std::cout << "Completed in " << durationMicro.count() << " microseconds" << std::endl;
	std::cout << "Completed in " << durationSec.count() << " seconds" << std::endl;

	std::cout << "Output array: " << std::endl << std::endl;
	printArr(board);
	return 0;
}
