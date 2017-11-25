#include <fstream>
#include <iostream>
#include <cstdlib>

#include "game.hpp"

using std::cout;
using std::cin;
using std::rand;

void Game::addShipFromPlayer(string, Board*)
{
    
}

void Game::addShipRandomly(string name, Board* board)
{
    bool valid = true;
    Ship ship;
    int length = getShipLengthFromName(name);
    
    ship.setLength(length);
    ship.setName(name);
    
    do
    {
        int orientation = rand() % 2;
        int x = 0, y = 0;
        
        if (orientation == 1) // horizontal
        {
            x = rand() % (10 - length);
            y = rand() % 10;
            ship.setOrientation(HORIZONTAL);
        }
        else // vertical
        {
            x = rand() % 10;
            y = rand() % (10 - length);
            ship.setOrientation(VERTICAL);
        }
        
        ship.setPosX(x);
        ship.setPosY(y);
        
        try
        {
            board->addShip(ship);
        }
        catch (ExceptionShipPlacementOccupied)
        {
            valid = false;
        }
    } while (!valid);
}

void Game::readShips(Board *board)
{
    ifstream file("./ship_placement.csv");
    file.ignore(256, '\n'); // ignore first line
    
    for (int shipCount = 5; shipCount > 0; shipCount--)
    {
        string name;
        char x, y;
        char orientation;
        
        getline(file, name, ',');
        name = toLowercase(name);
        
        file >> x;
        file >> y;
        file.ignore(); // ignore comma
        
        file >> orientation;
        file.ignore(2); // go to next line
        
        Ship newShip = Ship(name, int(x - 'A'), int(y - '1'), orientation);
        
        try
        {
            board->addShip(newShip);
        }
        catch (ExceptionShipOutOfBounds)
        {
            clearScreen();
            cout << "The " << name << " from the file was out of bounds.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                addShipFromPlayer(name, board);
            }
            else
            {
                addShipRandomly(name, board);
            }
        }
        catch (ExceptionShipPlacementOccupied)
        {
            clearScreen();
            cout << "The position for the " << name << " read in from the file was occupied by another ship.\n\n"
            << "Would you like to:\n1) Enter a new position\n2) Get a random position";
            
            if (getMenuChoice(2) == 1)
            {
                addShipFromPlayer(name, board);
            }
            else
            {
                addShipRandomly(name, board);
            }
        }
    }
    
    file.close();
}

void Game::randomizeShips(Board *board)
{
    // Adds one ship of each kind to a random location
    // on the given board.
    
    for (auto ship : SHIPTYPES)
    {
        addShipRandomly(ship.first, board);
    }
}

void Game::start()
{
    // This function sets up a game.
    // It prints the title, creates boards of specific types
    // (human or computer), gets the names of the players, and when the game
    // is over it asks if the players would like to play again.
    
    srand(int(time(NULL)));
    
    // Display main menu
    clearScreen();
    cout << "\n\nWelcome to Battleship!\n\n";
    cout << "Main Menu\n1) Single player game\n2) Two player game";
    singlePlayer = getMenuChoice(2) == 1;
    clearScreen();
    
    if(singlePlayer)
    {
        // Setup single player game
        string name;
        boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Computer);
        
        if (!debug)
        {
            cout << "Please enter your name: ";
            name = getStringInput();
            boards[0] -> setName(name);
        }
            
        readShips(boards[0]); // Read ships from file for player
        randomizeShips(boards[1]); // Get a random ship layout for AI
    }
    else
    {
        // Setup multiplayer game
        string name;
        
        boards[0] = new Board(Board::PlayerType::Human), boards[1] = new Board(Board::PlayerType::Human);
        
        cout << "Player 1, please enter your name: ";
        name = getStringInput();
        boards[0] -> setName(name);
        
        clearScreen();
        cout << "Player 2, please enter your name: ";
        name = getStringInput();
        boards[0] -> setName(name);
    }
    
    // Now that the game is set up, we may run it.
    run();
    
    cout << *boards[0];
    
    // Delete all board pointers in boards array
    for (auto boardPointer : boards)
    {
        delete boardPointer;
    }
    
    clearScreen();
}

void Game::run()
{
    bool gameOver = false;
    
    
    while (!gameOver)
    {
        gameOver = true;
    }
}
