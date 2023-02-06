# CMakeList.txt : CMake project for sudoku-solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Sudoku Library
file(GLOB_RECURSE sudokusources "${CMAKE_CURRENT_LIST_DIR}/include/*.h" "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp" "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")
add_library(sudoku-solver-lib STATIC ${sudokusources})
target_include_directories(sudoku-solver-lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# Runner executable
add_executable (sudoku-solver main.cpp)
target_link_libraries(sudoku-solver PUBLIC sudoku-solver-lib)

if(BUILD_SUDOKU_TESTS)
# Tests
file(GLOB_RECURSE sudokutests "${CMAKE_CURRENT_LIST_DIR}/test/*.cpp")
add_executable(
  sudoku-solver-test
  ${sudokutests}
)
target_link_libraries(
    sudoku-solver-test
    PUBLIC
    sudoku-solver-lib
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(sudoku-solver-test)
endif(BUILD_SUDOKU_TESTS)

