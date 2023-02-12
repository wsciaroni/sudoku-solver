# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("sudoku-solver")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# To organize projects in VisualStudio:
if(MSVC)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif(MSVC)

option(BUILD_SUDOKU_TESTS OFF)
option(CODE_COVERAGE OFF)

### Tests setup
if(BUILD_SUDOKU_TESTS)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif(MSVC)
FetchContent_MakeAvailable(googletest)

if(MSVC)
  set_target_properties(gtest PROPERTIES FOLDER "external/Google")
  set_target_properties(gmock PROPERTIES FOLDER "external/Google")
  set_target_properties(gtest_main PROPERTIES FOLDER "external/Google")
  set_target_properties(gmock_main PROPERTIES FOLDER "external/Google")
endif(MSVC)

enable_testing()
include(CTest)
endif(BUILD_SUDOKU_TESTS)

### Code Coverage
if(CMAKE_BUILD_TYPE STREQUAL "coverage" OR CODE_COVERAGE)
    if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        message("Building with llvm Code Coverage Tools")

        # Warning/Error messages
        if(NOT LLVM_COV_PATH)
            message(FATAL_ERROR "llvm-cov not found! Aborting.")
        endif()

        # set Flags
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

    elseif(CMAKE_COMPILER_IS_GNUCXX)
        message("Building with lcov Code Coverage Tools")

        # Warning/Error messages
        if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
            message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
        endif()

        find_program(LCOV_PATH lcov)
        if(NOT LCOV_PATH)
            message(FATAL_ERROR "lcov not found! Aborting...")
        endif()
        find_program(GENHTML_PATH lcov)
        if(NOT GENHTML_PATH)
            message(FATAL_ERROR "genhtml not found! Aborting...")
        endif()

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    else()
        message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
    endif()
endif()

# Include sub-projects.
add_subdirectory ("sudoku-solver")
