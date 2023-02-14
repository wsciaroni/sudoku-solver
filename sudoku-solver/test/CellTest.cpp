#include <gtest/gtest.h>

#include<Cell.h>

// Demonstrate some basic assertions.
TEST(CellTest, Initialization_IsSet) {
    Cell c;
    EXPECT_FALSE(c.valueIsSet());
}

TEST(CellTest, Initialization_GetValue) {
    Cell c;
    EXPECT_THROW(c.getValue(),std::logic_error);
}

TEST(CellTest, Initialization_GetNumRemainingPossibilities) {
    Cell c;
    EXPECT_EQ(c.getNumberOfRemainingPossibilities(), 9);
}

TEST(CellTest, Initialization_CheckIfValueCouldBe) {
    Cell c;

    for(int i = 1; i <= 9; i++) {
        EXPECT_TRUE(c.checkIfValueCouldBe(i));
    }
}

TEST(CellTest, Initialization_CheckIfValueCouldNOTBe) {
    Cell c;

    for(int i = 1; i <= 9; i++) {
        EXPECT_FALSE(c.checkIfValueCouldNotBe(i));
    }
}

TEST(CellTest, Initialization_GetRemainingPossiblities) {
    Cell c;

    std::list<int> remainingPossible = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    EXPECT_EQ(c.getRemainingPossiblities(), remainingPossible);
}

TEST(CellTest, CopyCell) {
    Cell c;

    EXPECT_NO_THROW(c.setCellValue(2));

    Cell c2;
    EXPECT_NO_THROW(c2 = c);
        
    EXPECT_EQ(c.getValue(), c2.getValue());
    EXPECT_EQ(c.valueIsSet(), c2.valueIsSet());
}

TEST(CellTest, OutOfRangeChecks) {
    Cell c;
    EXPECT_THROW(c.checkIfValueCouldBe(0), std::out_of_range);
    EXPECT_THROW(c.checkIfValueCouldBe(10), std::out_of_range);

    EXPECT_THROW(c.checkIfValueCouldNotBe(0), std::out_of_range);
    EXPECT_THROW(c.checkIfValueCouldNotBe(10), std::out_of_range);
}

TEST(CellTest, getRemainingPossibility) {
    Cell c;
    EXPECT_THROW(c.getRemainingPossibility(), std::logic_error);

    EXPECT_NO_THROW(c.excludeValue(1));
    EXPECT_NO_THROW(c.excludeValue(2));
    EXPECT_NO_THROW(c.excludeValue(3));
    
    EXPECT_NO_THROW(c.excludeValue(5));
    EXPECT_NO_THROW(c.excludeValue(6));
    EXPECT_NO_THROW(c.excludeValue(7));
    EXPECT_NO_THROW(c.excludeValue(8));
    EXPECT_NO_THROW(c.excludeValue(9));
    
    EXPECT_EQ(c.getRemainingPossibility(), 4);

    Cell c2;
    EXPECT_NO_THROW(c2.setCellValue(2));
    EXPECT_EQ(c2.getRemainingPossibility(), 2);
}

TEST(CellTest, excludeValue) {
    Cell c;
    EXPECT_NO_THROW(c.excludeValue(1));

    std::list<int> remainingPossible = { 2, 3, 4, 5, 6, 7, 8, 9 };
    EXPECT_EQ(c.getRemainingPossiblities(), remainingPossible);
    EXPECT_EQ(c.getNumberOfRemainingPossibilities(), 8);

    EXPECT_NO_THROW(c.excludeValue(1));
    EXPECT_EQ(c.getRemainingPossiblities(), remainingPossible);
    EXPECT_EQ(c.getNumberOfRemainingPossibilities(), 8);

    EXPECT_FALSE(c.checkIfValueCouldBe(1));
    EXPECT_TRUE(c.checkIfValueCouldNotBe(1));

    EXPECT_NO_THROW(c.setCellValue(2));

    EXPECT_THROW(c.excludeValue(2), std::logic_error);
    EXPECT_THROW(c.excludeValue(0), std::out_of_range);
    EXPECT_THROW(c.excludeValue(10), std::out_of_range);
}

TEST(CellTest, setValue) {
    Cell c;

    EXPECT_THROW(c.setCellValue(0), std::out_of_range);
    EXPECT_THROW(c.setCellValue(10), std::out_of_range);

    EXPECT_NO_THROW(c.excludeValue(2));
    EXPECT_THROW(c.setCellValue(2),std::logic_error);

    EXPECT_NO_THROW(c.setCellValue(1));
    EXPECT_NO_THROW(c.setCellValue(1));
    EXPECT_FALSE(c.checkIfValueCouldNotBe(1));
    EXPECT_TRUE(c.checkIfValueCouldBe(1));
    for(int i = 2; i <= 9; i++) {
        EXPECT_THROW(c.setCellValue(i), std::logic_error);
        EXPECT_TRUE(c.checkIfValueCouldNotBe(i));
        EXPECT_FALSE(c.checkIfValueCouldBe(i));
    }

    EXPECT_THROW(c.setCellValue(0), std::logic_error);
    EXPECT_THROW(c.setCellValue(10), std::logic_error);
}