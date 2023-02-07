#pragma once

#include <array>

class SudokuValidator
{
private:
    /* data */
public:
    static bool isSudokuValid(std::array<std::array<char, 9>, 9>& board);
};
