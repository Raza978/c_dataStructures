#include <stdio.h>
#include "log.h"
#include "bubbleSort.h"

int main(void)
{
    LOG_INFO_N("Hello world");
    //Update makefile to build/compile everything in the build folder and have the output in the build folder as well.
    //Add different folders for different data structures and algorithms. First need to figure out how to organize this project.
    // Add log.h and maybe simplify prefix information in the log macros.

    //update bubblesort to be my own code and not just copied from the internet.

    //First create basic data structure. Then should have a menu? or something else to run different data structures and modify the data structures.
    //Each data structure should be in a seperate file with its own header file. Then the main.c file can call the different data structure test functions to run them.

    //create a cheat sheet in one note that has list of data structures and algorithms and their big o notation? Plust worst to best big o notation outputs? nlogn vs n^2 which is worse?

    BubbleSort();

    return 0;
}