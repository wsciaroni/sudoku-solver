#include "Cell.h"

#include <stdexcept>

void Cell::throwIfOutOfRange(int i) const
{
    if(i < 1) {
        throw std::out_of_range("Invalid value (i < 1) for sudoku Cell");
    }

    if(i > SUDOKU_SIZE) {
        throw std::out_of_range("Invalid value (i > 9) for sudoku Cell");
    }
}

bool Cell::valueIsSet() const
{
    return isSet;
}

uint8_t Cell::getValue() const
{
    if(!valueIsSet()) throw std::logic_error("You got the value of a cell that has not been set!");
    return value;
}

uint8_t Cell::getNumberOfRemainingPossibilities() const
{
    return numberOfPossibilitiesRemaining;
}

bool Cell::checkIfValueCouldBe(int i) const
{
    if(valueIsSet()) return i == getValue();
    
    throwIfOutOfRange(i);

    return !constraints.test(i);
}

bool Cell::checkIfValueCouldNotBe(int i) const
{
    return !checkIfValueCouldBe(i);
}

void Cell::excludeValue(int excludedValue)
{
    if(valueIsSet() && getValue() == excludedValue) throw std::logic_error("Attempting to set an exclude for the value of the cell is illogical");
    
    throwIfOutOfRange(excludedValue);

    if(checkIfValueCouldBe(excludedValue)) {
        constraints.set(excludedValue);
        numberOfPossibilitiesRemaining--;
    }
}

int Cell::getRemainingPossibility() const
{
    if(getNumberOfRemainingPossibilities() != 1) throw std::logic_error("There are more than 1 remaining possibilities");

    if(valueIsSet()) return getValue();
    
    // We've reached the last posibility for the individual value
    int retVal = -1;
	for (int v = 1; v <= SUDOKU_SIZE; v++) {
		if (checkIfValueCouldBe(v)) {
			retVal = v;;
		}
	}
    return retVal;
}

std::list<int> Cell::getRemainingPossiblities() const
{
    std::list<int> retVect;

    for(int i = 1; i <= SUDOKU_SIZE; i++) {
        if(checkIfValueCouldBe(i)) {
            retVect.push_back(i);
        }
    }

    return retVect;
}

void Cell::setCellValue(int i)
{
    if(valueIsSet()) {
        if(getValue() == i) {
            return;
        }
        throw std::logic_error("Attempting to set value that's already set to a different value");
    }

    if(checkIfValueCouldNotBe(i)) throw std::logic_error("Attempt to set the value failed! We already determined that can't be");

    constraints = std::bitset<10>(0b1111111111); // 10 ones
    constraints.reset(i);
    numberOfPossibilitiesRemaining = 1;
    value = i;
    isSet = true;
}
