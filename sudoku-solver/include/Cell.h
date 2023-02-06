#pragma once

#include <bitset>

class Cell {
public:
   // The true value of the cell
   uint8_t value = 0;
   bool valueIsSet = false;

   // Number of possible unconstrained values for the cell
   uint8_t numberOfPossibilities = 9;

   std::bitset<10> constraints = 0b0000000000; // 0b1111111111;
};
