#include "SudokuValidator.h"

#include <set>

bool SudokuValidator::isSudokuValid(std::array<std::array<char, 9>, 9>& board)
{
    const std::set<char> correctSet = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Check each row
    std::set<char> currentRow;
    for(int i = 0; i < 9; i++) {
        currentRow.clear();

        for(int j = 0; j < 9; j++) {
            auto& v = board[i][j];
            currentRow.insert(v);
        }

        if(correctSet != currentRow) return false;
    }

    std::set<char> currentCol;
    for(int i = 0; i < 9; i++) {
        currentCol.clear();

        for(int j = 0; j < 9; j++) {
            auto& v = board[j][i];
            currentCol.insert(v);
        }

        if(correctSet != currentCol) return false;
    }

    std::set<char> currentBlock;
    for(int i = 0; i < 3; i++) {
        int rowOffset = i*3;
        for(int j = 0; j < 3; j++) {
            int colOffset = j*3;
            currentBlock.clear();
            
            for(int x = rowOffset; x < rowOffset+3; x++) {
                for(int y = colOffset; y < 3+colOffset; y++) {
                    auto& v = board[x][y];
                    currentBlock.insert(v);
                }
            }

            if(correctSet != currentBlock) return false;
        }
    }

    return true;
}