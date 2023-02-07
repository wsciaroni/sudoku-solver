#include <gtest/gtest.h>

#include<SudokuValidator.h>
#include<sudoku-solver.h>

// Demonstrate some basic assertions.
TEST(SudokuSolveTest, BasicTest) {

   std::array<std::array<char, 9>, 9> board = { {
       {'5','3','.','.','7','.','.','.','.'},
       {'6','.','.','1','9','5','.','.','.'},
       {'.','9','8','.','.','.','.','6','.'},
       {'8','.','.','.','6','.','.','.','3'},
       {'4','.','.','8','.','3','.','.','1'},
       {'7','.','.','.','2','.','.','.','6'},
       {'.','6','.','.','.','.','2','8','.'},
       {'.','.','.','4','1','9','.','.','5'},
       {'.','.','.','.','8','.','.','7','9'}} };
        
    Solution s;
    s.solveSudoku(board);
  // Expect equality.
  EXPECT_TRUE(SudokuValidator::isSudokuValid(board));
}


TEST(SudokuSolveTest, BasicFailTest) {
    // Notice the two 7s. This is an invalid input
   std::array<std::array<char, 9>, 9> board = { {
       {'5','3','.','.','7','7','.','.','.'},
       {'6','.','.','1','9','5','.','.','.'},
       {'.','9','8','.','.','.','.','6','.'},
       {'8','.','.','.','6','.','.','.','3'},
       {'4','.','.','8','.','3','.','.','1'},
       {'7','.','.','.','2','.','.','.','6'},
       {'.','6','.','.','.','.','2','8','.'},
       {'.','.','.','4','1','9','.','.','5'},
       {'.','.','.','.','8','.','.','7','9'} } };

    Solution s;
    s.solveSudoku(board);
    // Expect equality.
    EXPECT_FALSE(SudokuValidator::isSudokuValid(board));
}