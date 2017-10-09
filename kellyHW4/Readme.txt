*******************************************************
*  Name      :  Cody Kelly
*  Student ID:  101886601
*  Class     :  CSCI 2312           
*  HW#       :  4                
*  Due Date  :  October 10th, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

This programs reads in info about various animals,
performs operations on their data, then outputs the 
results.


*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program. Asks user for input, then outputs results.

Name: animal.hpp
   Definitions of animal classes. Contains member 
   definitions for each animal class.

Name: animal.cpp
   Animal implementation. Implements functions for the each
   animal class.
   
   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on gnu g++ 4.2.1
   and CSEgrid
	

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip kellyHW4

   Now you should see a directory named homework with the files:
        main.cpp
	animal.cpp
	animal.hpp
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd kellyHW4

    Compile the program by:
    % make

3. Run the program by:
   % ./main

4. Delete the obj files, executables, and core dump by
   %./make clean
