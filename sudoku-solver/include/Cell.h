#pragma once

#include <bitset>

/**
 * @brief Information at a specific coordinate on a sudoku board
 * 
 */
class Cell {
public:
   /// The true value of the cell
   uint8_t value = 0;

   /// Value of the cell has been confirmed
   bool valueIsSet = false;

   /// Number of possible unconstrained values for the cell
   uint8_t numberOfPossibilities = 9;

   /**
    * @brief Holds what values are possible
    * 
    * I am ignoring Index 0.
    * For indicies 1 through 9, if the bit is set, then that index cannot be the value
    */
   std::bitset<10> constraints = 0b0000000000; // 0b1111111111;
};
