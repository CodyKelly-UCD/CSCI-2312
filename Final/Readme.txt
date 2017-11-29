*******************************************************
*  Name      :  Cody Kelly
*  Student ID:  101886601
*  Class     :  CSCI 2312           
*  HW#       :  Final
*  Due Date  :  November 26th, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

Before I say anything else - I definitely did the extra
credit for this project. If you’re testing the program,
you’ll have to select Classic mode (option 1), then 
single player (option 1 again). That will take you to 
the game mode that was asked for in the project 
requirements. All the other modes are just extras I 
threw in.

Anyway..

This is the game of Battleship! Available for one or two
players are the following game modes:

Classic mode:
Each player gives a coordinate of attack on their turn,
with the goal of sinking all of their opponent’s ships!
The first player to sink the other’s ships wins.

Salvo mode:
In this mode, each player shoots as many shots as they
have boats. If one of their fleet is sunk, they have one
less shot in their salvo. This is recommended for more
advanced players.

For one player games, the player can choose the
skill of their computer opponent. Extreme mode is only
for the bravest admirals!

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This starts the game.

Name:  battleship.cpp
   This file holds globals used all over the program.

Name:  board.cpp
   This class provides functions for using 
   boards in the game. Boards control adding and using
   ships, attacking, marking attacks, etc.

Name:  grid.cpp
   This class holds a variable-sized grid of chars

Name:  game.cpp
   This class sets up and runs the main game loop

Name:  ship.cpp
   This class contains functions to use ships
   
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
       % unzip kellyFinal

   Now you should see a directory named homework with the files:
        main.cpp
	battleship.cpp
	battleship.hpp
	board.cpp
	board.hpp
	game.cpp
	game.hpp
	grid.cpp
	grid.hpp
	ship.cpp
	ship.hpp
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd kellyFinal

    Compile the program by:
    % make

3. Run the program by:
   % ./main

4. Delete the obj files, executables, and core dump by
   %./make clean
