// sudoku-solver.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <bitset>
#include <vector>
#include <cassert>
#include <algorithm>

class Cell {
public:
   // The true value of the cell
   uint8_t value = 0;
   bool valueIsSet = false;

   // Number of possible unconstrained values for the cell
   uint8_t numberOfPossibilities = 9;

   std::bitset<10> constraints = 0b0000000000; // 0b1111111111;
};

class Solution {
   bool loggingEnabled = false;

   void inline printVectorState(std::vector<std::vector<Cell>>& vect) {
      if (!loggingEnabled) return;
      std::cout << "[" << std::endl;
      for (int i = 0; i < 9; i++) {
         std::cout << "[";
         for (int j = 0; j < 9; j++) {
            std::cout << "\"" << (char)(vect[i][j].value + '0') << "\"";
         }
         std::cout << "]," << std::endl;
      }
      std::cout << "]" << std::endl;
   }

   void inline initialize() {
      cells.resize(9);
      for (auto& arr : cells) {
         arr.resize(9);
      }

      for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
            cells[i][i].value = 0;
         }
      }

      if (loggingEnabled) {
         std::cout << "Initialzied all cells" << std::endl;
      }
   }

   bool inline setValue(int i, int j, int value) {
      if (loggingEnabled) {
         std::cout << "Setting value at: [" << i << "," << j << "]: " << (char)(value + '0') << std::endl;
      }
      Cell& c = cells[i][j];

      // We've already determined this value and it matches
      if (c.valueIsSet && c.value == value) {
         if (loggingEnabled) {
            std::cout << "Value already set" << std::endl;
         }
         return true;
      }

      // If we've already deterimined that this cell can't be this value, return false
      if (c.constraints[value]) {
         if (loggingEnabled) {
            std::cout << "Cannot set, this violates the constraints from earlier..." << std::endl;
         }
         return false;
      }

      if (loggingEnabled) {
         std::cout << "Setting this value." << std::endl;
      }

      c.constraints = std::bitset<10>(0b1111111111); // 10 ones
      c.constraints.reset(value);
      c.numberOfPossibilities = 1;
      c.value = value;
      c.valueIsSet = true;

      for (int k = 0; k < 9; k++) {
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

   bool inline updateConstraints(int i, int j, int excludedValue) {
      if (loggingEnabled) {
         std::cout << "Attempting to exclude the value " << (char)(excludedValue + '0') << " at [" << i << "," << j << "]" << std::endl;
      }
      Cell& c = cells[i][j];

      if (c.constraints[excludedValue]) {
         if (loggingEnabled) {
            std::cout << "Constraints already set" << std::endl;
         }
         return true;
      }
      if (c.valueIsSet && c.value == excludedValue) {
         if (loggingEnabled) {
            std::cout << "Can't constrain field. Value already set" << std::endl;
         }
         return false; // We were wrong in our attempt
      }

      // If the value could be valid, AND the constraints don't have this excluded, let's remove it from the constraints
      c.constraints.set(excludedValue);
      c.numberOfPossibilities--;

      if (c.numberOfPossibilities > 1) return true; // If we haven't reached the last number of possibilities

      // We've reached the last posibility for the individual value
      for (int v = 1; v <= 9; v++) {
         if (!c.constraints[v]) {
            return setValue(i, j, v);
         }
      }

      // This should never happen
      // throw std::logic_error("Somehow the Cell has 1 possibility remaining, but none available in the set function");
      assert(false);
   }

   // Keep a list of empty cells at the beginning to back track
   std::vector<std::pair<int, int>> bt;

   void inline sortBt(const std::vector<std::pair<int, int>>::iterator & it) {
      // Sort the list by the number of possibilites remaining in each cell
      std::sort(it, bt.end(), [this](const std::pair<int, int>& a, const std::pair<int, int>& b) {
         return cells[a.first][a.second].numberOfPossibilities < cells[b.first][b.second].numberOfPossibilities;
      });
   }

   bool inline findValuesForEmptyCells() {
      bt.clear();

      for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
            if (!cells[i][j].valueIsSet) {
               bt.emplace_back(i, j);
            }
         }
      }

      // Sort the list by the number of possibilites remaining in each cell
      sortBt(bt.begin());
      return backtrack(bt.begin());
   }

   bool inline backtrack(std::vector<std::pair<int, int>>::iterator k) {
      if (k == bt.end()) return true;

      auto i = (*k).first;
      auto j = (*k).second;

      // Fast path
      if (cells[i][j].valueIsSet) {
         if (loggingEnabled) {
            std::cout << "BSorting: " << std::distance(k + 1, bt.end()) << " elements" << std::endl;
         }
         sortBt(k + 1);
         return backtrack(k + 1);
      }

      auto constraints = cells[i][j].constraints;

      auto snapshot = cells; // Create a copy of the array as a backup

      for (int v = 1; v <= 9; v++) {
         if (!constraints[v]) {
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
      }
      return false;
   }

   std::vector<std::vector<Cell>> cells; // 9x9 vector of cell

public:
   void solveSudoku(std::vector<std::vector<char>>& board) {
      initialize();

      for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
               if (!setValue(i, j, board[i][j] - '0'))
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

      for (int i = 0; i < 9; i++) {
         for (int j = 0; j < 9; j++) {
            if (cells[i][j].valueIsSet) {
               board[i][j] = cells[i][j].value + '0';
            }
         }
      }

      printVectorState(cells);
   }
};
