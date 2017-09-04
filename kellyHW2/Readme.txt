*******************************************************
*  Name      :  Cody Kelly
*  Student ID:  101886601
*  Class     :  CSCI 2312           
*  HW#       :  2                
*  Due Date  :  September 12th, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

Builds two grids which are each X wide and Y long where X and Y are user inputs to determine the size of the grids.  Fills each cell of both grids with a ‘0’.  Randomly fills 1/3 of the grid’s cells with a ‘1’.  Randomly fills each of the two grids separately so they do not have the all of the same squared filled with a ‘1’.  Compares the two grids (square by square comparison) to find squares which have a ‘1’ in both grids.  Creates a third grid which contains a ‘1’ in squares where both of the compared grids contain a ‘1’ and has a ‘0’ in any other square.


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This is the driver program that calls sub-functions
   to read data from an input file, use the data to create two matrices,
   and compute and display their sum and product.

Name: grid.hpp
   Grid definition. Contains member and friend definitions for the Grid class.

Name: grid.cpp
   Grid implementation. Implements functions for the Grid class.
   
   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on gnu g++ 4.4.2.  It was 
   compiled, run, and tested on gcc ouray.cudenver.edu.


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip kellyHW2

   Now you should see a directory named homework with the files:
        main.cpp
	grid.cpp
	grid.hpp
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd kellyHW2

    Compile the program by:
    % make

3. Run the program by:
   % ./main

4. Delete the obj files, executables, and core dump by
   %./make clean
