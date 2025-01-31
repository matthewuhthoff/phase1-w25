# This is the main CMake configuration file
# Make sure CMake is synced whenever you make the changes
cmake_minimum_required(VERSION 3.24)
project(my-mini-compiler C)

set(CMAKE_C_STANDARD 11)

# Add include directory (this will be needed to add your tokens to your lexer)
include_directories(${PROJECT_SOURCE_DIR}/phase1-w25/include)

# #find all the .c files in the src directory (don't put random .c files in the src directory or they will be compiled brrr)
# file(GLOB_RECURSE SOURCES "phase1-w25/src/**/*.c")

# Add executables when needed: Make sure you specify the path to your .c or .h file
# add_executable(my-mini-compiler ${SOURCES})
add_executable(my-mini-compiler
        phase1-w25/src/lexer/lexer.c
        phase1-w25/src/regex/custom_regex.c)
        
