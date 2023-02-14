#pragma once

#include <bitset>
#include <list>

/**
 * @brief Information at a specific coordinate on a sudoku board
 * 
 */
class Cell {
private:
   int SUDOKU_SIZE = 9;

   /// The true value of the cell
   uint8_t value = 0;

   /// Value of the cell has been confirmed
   bool isSet = false;

   /// Number of possible unconstrained values for the cell
   uint8_t numberOfPossibilitiesRemaining = 9;

   /**
    * @brief Holds what values are possible
    * 
    * I am ignoring Index 0.
    * For indicies 1 through 9, if the bit is set, then that index cannot be the value
    */
   std::bitset<10> constraints = 0b0000000000; // 0b1111111111;

   /**
    * @brief Check the value i for valid index of values
    * @throws std::out_of_range if i is less than 1 or greater than 9
   */
   void throwIfOutOfRange(int i) const;

public:
   /**
    * @brief Check if the Cell has been set
    * @return true if the value has been set
   */
   bool valueIsSet() const;
   
   /**
    * @brief Get the value of the cell
    * @return value of the cell
    * @throws std::logic_error if the Cell has not been set
   */
   uint8_t getValue() const;

   /**
    * @brief Get the number of remaining possibilities
    * @return The number of possibilities for this cell. 1 if set
   */
   uint8_t getNumberOfRemainingPossibilities() const;

   /** @brief Could this cell possibly be i
    *  @param i The value to check
    *  @return True if the value could be or is `i`
    *  @throws std::out_of_range if i is not a valid possibility
    */
   bool checkIfValueCouldBe(int i) const;

   /**
    * @brief Have we determined that this cell is definitely not this value
    * @param i The value to check
    * @return True if the value is definitely NOT `i`
    * @throws std::out_of_range if i is not a valid possibility
   */
   bool checkIfValueCouldNotBe(int i) const;

   /**
    * @brief Update the constraint to know that this IS NOT the value in this cell
    * @param excludedValue The value to reject
    * @throws std::logic_error If the value is inconsistent
    * @throws std::out_of_range If the value is not valid
   */
   void excludeValue(int excludedValue);

   /**
    * @brief Get the value of the last possible value
    * @return The value of the last possible value
    * @throws std::logic_error if there are more than one possibilities
    * 
    * In theory, this could throw std::out_of_range... That should never happen
   */
   int getRemainingPossibility() const;

   /**
    * @brief Get the possible values
    * @return List of the remaining possibilities
    * 
    * In theory, this could throw std::out_of_range... That should never happen
   */
   std::list<int> getRemainingPossiblities() const;

   /**
    * @brief Sets the value of the cell authoritatively
    * @param i The value of the cell
    * @throws std::out_of_range If the cell is not set and the value is out of range
    * @throws Std::logic_error If the cell cannot be this value
   */
   void setCellValue(int i);
};
