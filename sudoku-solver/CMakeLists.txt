# CMakeList.txt : CMake project for sudoku-solver, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE sudokusources "${CMAKE_CURRENT_LIST_DIR}/include/*.h" "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp" "${CMAKE_CURRENT_LIST_DIR}/source/*.cpp")
add_library(sudoku-solver-lib STATIC ${sudokusources})
target_include_directories(sudoku-solver-lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

# Add source to this project's executable.
add_executable (sudoku-solver main.cpp)

target_link_libraries(sudoku-solver PUBLIC sudoku-solver-lib)

# TODO: Add tests and install targets if needed.
