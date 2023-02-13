#include "Cell.h"

#include <stdexcept>

bool Cell::valueIsSet() const {
    return isSet;
}

uint8_t Cell::getValue() const
{
    return value;
}

uint8_t Cell::getNumberOfRemainingPossibilities() const
{
    return numberOfPossibilitiesRemaining;
}

bool Cell::checkIfValueCouldBe(int i) const
{
    if(valueIsSet()) return i == getValue();

    return !constraints.test(i);
}

bool Cell::checkIfValueCouldNotBe(int i) const
{
    return !checkIfValueCouldBe(i);
}

void Cell::excludeValue(int excludedValue)
{
    constraints.set(excludedValue);
    numberOfPossibilitiesRemaining--;
}

int Cell::getRemainingPossibility() const
{
    if(getNumberOfRemainingPossibilities() != 1) throw std::logic_error("There are more than 1 remaining possibilities");
    
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
    if(checkIfValueCouldNotBe(i)) throw std::logic_error("Attempt to set the value failed! We already determined that can't be");

    constraints = std::bitset<10>(0b1111111111); // 10 ones
    constraints.reset(i);
    numberOfPossibilitiesRemaining = 1;
    value = i;
    isSet = true;
}
