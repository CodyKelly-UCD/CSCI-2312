*******************************************************
*  Name      :  Cody Kelly
*  Student ID:  101886601
*  Class     :  CSCI 2312           
*  HW#       :  3                
*  Due Date  :  September 26th, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This program allows input of a ship length, grid location, orientation, and dive depth.  Assumes the grid where the submarine is to be placed is a 10 by 10 grid. Randomly generates 15 torpedo shots, outputs the shot grid locations to the screen. Then outputs whether the submarine was hit or missed or sunk. Then creates a second submarine and uses an overloaded assignment operator to assign the values from the first submarine to the second submarine. Lastly, it prints out the information about the second submarine.


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program. Asks user for input, then outputs results.

Name: grid.hpp
   Grid definition. Contains member and friend definitions for the Grid class.

Name: grid.cpp
   Grid implementation. Implements functions for the Grid class.
   
   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on gnu g++ 4.2.1


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip kellyHW3

   Now you should see a directory named homework with the files:
        main.cpp
	grid.cpp
	grid.hpp
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd kellyHW3

    Compile the program by:
    % make

3. Run the program by:
   % ./main

4. Delete the obj files, executables, and core dump by
   %./make clean
